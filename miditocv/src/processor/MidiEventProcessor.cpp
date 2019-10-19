#include "MidiEventProcessor.h"

#define MIDI_CHANNELS 16

MidiEventProcessor::MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, GateOutput& gateOutput, PitchCvOutput& pitchCvOutput) :
        _config(config),
        _statusLedTask(statusLedTask),
        _gateOutput(gateOutput), 
        _pitchCvOutput(pitchCvOutput) {
    _channelMapping = new uint8_t[MIDI_CHANNELS];
    _lastNoteChannel = new uint8_t[_pitchCvOutput.getSize()];

    // get channel mappings from config
    for(uint8_t i = 0; i < MIDI_CHANNELS; i++) {
        _channelMapping[i] = _config.getCvChannelMapping(i).from;
    }
}

void MidiEventProcessor::eventNoteOn(uint8_t midiChannel, uint8_t note, uint8_t velocity) {

    uint8_t cvChannel = getCvOutputChannel(midiChannel);
    if(cvChannel == -1) {
        return;
    }

    _lastNoteChannel[cvChannel] = note;

    // convert note number to Pitch CV Output

    // convert velocity to Cv Output

    // send trigger and gate output

    _statusLedTask.blinkGreen();
}

void MidiEventProcessor::eventNoteOff(uint8_t midiChannel, uint8_t note) {

    uint8_t cvChannel = getCvOutputChannel(midiChannel, note);
    if(cvChannel == -1) {
        return;
    }

    // convert midi channel and note to Pitch Cv Channel

    // stop gate output

    _statusLedTask.blinkRed();
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

uint8_t MidiEventProcessor::getCvOutputChannel(uint8_t midiChannel, uint8_t note) {
    for(uint8_t i = 0; i < _pitchCvOutput.getSize(); i++) {
        if(_lastNoteChannel[i] == note) {
            return i;
        }
    }

    return -1;
}
