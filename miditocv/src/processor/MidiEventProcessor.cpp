#include "MidiEventProcessor.h"

#include <Arduino.h>

#define MIDI_CHANNELS 16

MidiEventProcessor::MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, GateOutput& gateOutput,
                                       PitchCvOutput& pitchCvOutput, MidiToPitchConverter& midiToPitchConverter) :
        _config(config),
        _statusLedTask(statusLedTask),
        _gateOutput(gateOutput),
        _pitchCvOutput(pitchCvOutput),
        _midiToPitchConverter(midiToPitchConverter) {
    _channelMapping = new uint8_t[MIDI_CHANNELS];
    _channelNoteMapping = new List[_pitchCvOutput.getSize()];

    // get channel mappings from config
    for(uint8_t i = 0; i < MIDI_CHANNELS; i++) {
        _channelMapping[i] = _config.getCvChannelMapping(i).from;
    }
}

void MidiEventProcessor::eventNoteOn(uint8_t midiChannel, int8_t note, uint8_t velocity) {

    uint8_t cvChannel = getCvOutputChannel(midiChannel);
    if(cvChannel == -1) {
        return;
    }

    saveNoteToChannel(cvChannel, note);

    // pitch cv
    float pitch = _midiToPitchConverter.convert(note, 0); //TODO set channel bend
    _pitchCvOutput.setVoltage(cvChannel, pitch);
    _pitchCvOutput.sendData();

    //TODO convert velocity to Cv Output

    //gate
    _gateOutput.setValue(cvChannel, HIGH);
    _gateOutput.sendData();

    _statusLedTask.blinkGreen();
}

void MidiEventProcessor::eventNoteOff(uint8_t midiChannel, int8_t note) {

    uint8_t cvChannel = getCvOutputChannelForNote(midiChannel, note);
    if(cvChannel == -1) {
        return;
    }

    bool notesStillPressed = clearNoteFromChannel(cvChannel, note);

    if(!notesStillPressed) {
        //gate
        _gateOutput.setValue(cvChannel, LOW);
        _gateOutput.sendData();

        //TODO turn off trigger output
        _statusLedTask.blinkRed();
    }
}


uint8_t MidiEventProcessor::getCvOutputChannel(uint8_t midiChannel) {
    uint8_t currentCvChannel = _channelMapping[midiChannel];
    ChannelMapping channelConfig = _config.getCvChannelMapping(midiChannel); //TODO handle no channel mapping

    if(channelConfig.from < channelConfig.to) {
        if(currentCvChannel == channelConfig.to) {
            _channelMapping[midiChannel] = channelConfig.from;
        } else {
            _channelMapping[midiChannel]++;
        }
    }

    return currentCvChannel;
}

uint8_t MidiEventProcessor::getCvOutputChannelForNote(uint8_t midiChannel, uint8_t note) {
    for(uint8_t i = 0; i < _pitchCvOutput.getSize(); i++) {
        if(_channelNoteMapping[i].find(note) != -1) {
            return i;
        }
    }

    return -1;
}

void MidiEventProcessor::saveNoteToChannel(uint8_t cvChannel, uint8_t note) {
    if(_channelNoteMapping[cvChannel].find(note) == -1) {
        _channelNoteMapping[cvChannel].append(note);
    }
}

bool MidiEventProcessor::clearNoteFromChannel(uint8_t cvChannel, uint8_t note) {
    int8_t index = _channelNoteMapping[cvChannel].find(note);
    if(index != -1) {
        _channelNoteMapping[cvChannel].remove(index);
    }
    return _channelNoteMapping[cvChannel].length > 0;
}

void MidiEventProcessor::eventSystemConfig(uint8_t* message, size_t size) {

}
