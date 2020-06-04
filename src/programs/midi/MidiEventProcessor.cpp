#include "MidiEventProcessor.h"

#include <Arduino.h>

#define CVBANK_NOTEVELOCITY 0
#define CVBANK_PERCUSSIONVELOCITY 2
#define CVBANK_PERCUSSIONCTRL1 3
#define CVBANK_PERCUSSIONCTRL2 4
#define GATEBANK_NOTEGATE 2
#define GATEBANK_NOTETRIG 1
#define GATEBANK_PERCTRIG 0
#define GATEBANK_CLOCK 3


MidiEventProcessor::MidiEventProcessor(Configuration& config,
                                       CvOutputService& cvOutputService,
                                       MidiToPitchConverter& midiToPitchConverter) :
        _config(config),
        _cvOutputService(cvOutputService),
        _midiToPitchConverter(midiToPitchConverter) {
    resetChannelMappings();
}


void MidiEventProcessor::eventNoteOn(uint8_t midiChannel, int8_t note, uint8_t velocity) {
    if(midiChannel == _config.getPercussionChannelConfig()->midiChannel) {
        eventPercussionTrigger(note, velocity);
    }

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
    _cvOutputService.setControlValue(cvChannel, CVBANK_NOTEVELOCITY, velocityVoltage);

    //gate
    _cvOutputService.setGateValue(cvChannel, GATEBANK_NOTEGATE, HIGH);

    //trigger
    _cvOutputService.setTrigger(cvChannel, GATEBANK_NOTETRIG);
}


void MidiEventProcessor::eventPercussionTrigger(int8_t note, uint8_t velocity) {
    xen_PercussionMapping* percussionMapping = _config.getPercussionMapping(note);
    if(percussionMapping == NULL) {
        return;
    }

    // velocity cv
    float velocityVoltage = _midiToPitchConverter.convertVelocity(velocity);
    _cvOutputService.setControlValue(percussionMapping->cvChannel, CVBANK_PERCUSSIONVELOCITY, velocityVoltage);

    // other control values
    _cvOutputService.setControlValue(percussionMapping->cvChannel, CVBANK_PERCUSSIONCTRL1, percussionMapping->control1Value);
    _cvOutputService.setControlValue(percussionMapping->cvChannel, CVBANK_PERCUSSIONCTRL2, percussionMapping->control2Value);

    //trigger
    _cvOutputService.setTrigger(percussionMapping->cvChannel, GATEBANK_PERCTRIG);
}


void MidiEventProcessor::eventNoteOff(uint8_t midiChannel, int8_t note) {
    int8_t cvChannel = getCvOutputChannelForNote(midiChannel, note);
    if(cvChannel == -1) {
        return;
    }

    bool notesStillPressed = clearNoteFromChannel(cvChannel, note);

    if(!notesStillPressed) {
        //gate
        _cvOutputService.setGateValue(cvChannel, GATEBANK_NOTEGATE, LOW);
    }
}


void MidiEventProcessor::eventNotePressure(uint8_t midiChannel, int8_t note, int8_t pressure) {
    int8_t cvChannel = getCvOutputChannelForNote(midiChannel, note);
    if(cvChannel == -1) {
        return;
    }

    // velocity cv
    float velocityVoltage = _midiToPitchConverter.convertVelocity(pressure);
    _cvOutputService.setControlValue(cvChannel, CVBANK_NOTEVELOCITY, velocityVoltage);
}


void MidiEventProcessor::eventChannelPressure(uint8_t midiChannel, int8_t pressure) {
    xen_ChannelMapping* channelConfig = _config.getCvChannelMapping(midiChannel);
    if(channelConfig == NULL) {
        return;
    }

    for(int8_t cvChannel = channelConfig->cvChannelFrom; cvChannel <= channelConfig->cvChannelTo; cvChannel++) {
        if(_channelNoteMapping[cvChannel].length > 0) {

            // velocity cv
            float velocityVoltage = _midiToPitchConverter.convertVelocity(pressure);
            Serial.println("MidiEventProcessor::eventChannelPressure");
            Serial.println(pressure);
            Serial.println(velocityVoltage);
            _cvOutputService.setControlValue(cvChannel, CVBANK_NOTEVELOCITY, velocityVoltage);
        }
    }
}


void MidiEventProcessor::eventControlChange(uint8_t midiChannel, int8_t controlNumber, int16_t value) {
    xen_ControllerMapping* controllerMapping = _config.getCvControllerMapping(midiChannel, controlNumber);
    if(controllerMapping == NULL) {
        return;
    }

    // velocity cv
    float controlVoltage = _midiToPitchConverter.convertControl(value);
    _cvOutputService.setControlValue(controllerMapping->cvChannel, controllerMapping->cvBank, controlVoltage);
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


void MidiEventProcessor::eventClock() {
    _cvOutputService.setTrigger(0, GATEBANK_CLOCK);
    _clockCounter++;
    if(_clockCounter == 24) {
        _clockCounter = 0;
        _cvOutputService.setTrigger(1, GATEBANK_CLOCK);
    }
}

void MidiEventProcessor::eventStart() {
    _clockCounter = 0;
}

void MidiEventProcessor::eventStop() {
}

void MidiEventProcessor::eventReset() {
    for(uint8_t cvChannel = 0; cvChannel < CV_CHANNELS; cvChannel++) {
        _channelNoteMapping[cvChannel].removeAll();
        _cvOutputService.setGateValue(cvChannel, GATEBANK_NOTEGATE, LOW);
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
