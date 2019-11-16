#include "MidiEventProcessor.h"

#include "src/hwconfig.h"
#include <Arduino.h>

#define MIDI_CHANNELS 16

MidiEventProcessor::MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask,
                                       CvOutputService& cvOutputService,
                                       MidiToPitchConverter& midiToPitchConverter) :
        _config(config),
        _statusLedTask(statusLedTask),
        _cvOutputService(cvOutputService),
        _midiToPitchConverter(midiToPitchConverter) {
    _channelMapping = new int8_t[MIDI_CHANNELS];
    _channelPitchBend = new float[MIDI_CHANNELS];
    _channelNoteMapping = new List[CV_CHANNELS];
    _channelNotePitch = new float[CV_CHANNELS];
    resetChannelMappings();
}


void MidiEventProcessor::eventNoteOn(uint8_t midiChannel, int8_t note, uint8_t velocity) {
    int8_t cvChannel = getCvOutputChannel(midiChannel);
    if(cvChannel == -1) {
        return;
    }

    saveNoteToChannel(cvChannel, note);

    // pitch cv
    float notePitch = _midiToPitchConverter.convertNote(note); //TODO set channel bend
    _channelNotePitch[cvChannel] = notePitch;
    _cvOutputService.setPitchValue(cvChannel, notePitch + _channelPitchBend[midiChannel]);

    // velocity cv
    float velocityVoltage = _midiToPitchConverter.convertVelocity(velocity);
    _cvOutputService.setControlValue(cvChannel, velocityVoltage);

    //gate
    _cvOutputService.setGateValue(cvChannel, HIGH);

    //trigger
    _cvOutputService.setTrigger(cvChannel);

    _statusLedTask.blinkGreen();
}


void MidiEventProcessor::eventNoteOff(uint8_t midiChannel, int8_t note) {
    int8_t cvChannel = getCvOutputChannelForNote(midiChannel, note);
    if(cvChannel == -1) {
        return;
    }

    bool notesStillPressed = clearNoteFromChannel(cvChannel, note);

    if(!notesStillPressed) {
        //gate
        _cvOutputService.setGateValue(cvChannel, LOW);

        //TODO turn off trigger output
        _statusLedTask.blinkRed();
    }
}


void MidiEventProcessor::eventNotePressure(uint8_t midiChannel, int8_t note, int8_t pressure) {
    // TODO find channel and update velocity output
}


void MidiEventProcessor::eventControlChange(uint8_t midiChannel, int8_t controlNumber, int8_t value) {
    // TODO figure out how to map control number to output channel
}


void MidiEventProcessor::eventPitchBend(uint8_t midiChannel, int16_t bend) {
    _channelPitchBend[midiChannel] = _midiToPitchConverter.convertBend(bend);

    xen_ChannelMapping* channelConfig = _config.getCvChannelMapping(midiChannel);
    if(channelConfig == NULL) {
        return;
    }

    for(int8_t cvChannel = channelConfig->cvChannelFrom; cvChannel <= channelConfig->cvChannelTo; cvChannel++) {
        _cvOutputService.setPitchValue(cvChannel, _channelNotePitch[cvChannel] + _channelPitchBend[midiChannel]);
    }
}


int8_t MidiEventProcessor::getCvOutputChannel(int8_t midiChannel) {
    uint8_t currentCvChannel = _channelMapping[midiChannel];
    xen_ChannelMapping* channelConfig = _config.getCvChannelMapping(midiChannel);
    if(channelConfig == NULL) {
        return -1;
    }

    if(channelConfig->cvChannelFrom < channelConfig->cvChannelTo) {
        if(currentCvChannel == channelConfig->cvChannelTo) {
            _channelMapping[midiChannel] = channelConfig->cvChannelFrom;
        } else {
            _channelMapping[midiChannel]++;
        }
    }

    return currentCvChannel;
}


int8_t MidiEventProcessor::getCvOutputChannelForNote(int8_t midiChannel, int8_t note) {
    for(uint8_t i = 0; i < CV_CHANNELS; i++) {
        if(_channelNoteMapping[i].find(note) != -1) {
            return i;
        }
    }

    return -1;
}


void MidiEventProcessor::saveNoteToChannel(int8_t cvChannel, int8_t note) {
    if(_channelNoteMapping[cvChannel].find(note) == -1) {
        _channelNoteMapping[cvChannel].append(note);
    }
}


bool MidiEventProcessor::clearNoteFromChannel(int8_t cvChannel, int8_t note) {
    int8_t index = _channelNoteMapping[cvChannel].find(note);
    if(index != -1) {
        _channelNoteMapping[cvChannel].remove(index);
    }
    return _channelNoteMapping[cvChannel].length > 0;
}


void MidiEventProcessor::resetChannelMappings() {
    // get initial channel mappings from config
    for(uint8_t i = 0; i < MIDI_CHANNELS; i++) {
        xen_ChannelMapping* channelConfig = _config.getCvChannelMapping(i);
        if(channelConfig != NULL) {
            _channelMapping[i] = channelConfig->cvChannelFrom;
        } else {
            _channelMapping[i] = -1;
        }
    }
}


void MidiEventProcessor::eventSystemConfig(uint8_t* message, size_t size) {
    _config.configUpdateMessage(message, size);
    resetChannelMappings();
}
