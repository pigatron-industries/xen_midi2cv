#include "MidiEventProcessor.h"


MidiEventProcessor::MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, PitchCvOutput& pitchCvOutput) :
        _config(config),
        _statusLedTask(statusLedTask),
        _pitchCvOutput(pitchCvOutput) {
    _channelMapping = new uint8_t[_pitchCvOutput.getSize()];

    // get channel mappings from config
    for(uint8_t i = 0; i < _pitchCvOutput.getSize(); i++) {
        _channelMapping[i] = _config.getCvChannelMapping(i).from;
    }
}

void MidiEventProcessor::eventNoteOn(uint8_t midiChannel, uint8_t note, uint8_t velocity) {
    _statusLedTask.blinkGreen();

    uint8_t cvChannel = getCvOutputChannel(midiChannel);

    // convert note number to Pitch CV Output

    // convert velocity to Cv Output

    // send trigger and gate output
}

void MidiEventProcessor::eventNoteOff(uint8_t midiChannel, uint8_t note) {
    _statusLedTask.blinkRed();

    // convert midi channel to Pitch Cv Channel

    // stop gate output
}


uint8_t MidiEventProcessor::getCvOutputChannel(uint8_t midiChannel) {
    uint8_t currentCvChannel = _channelMapping[midiChannel];
    ChannelMapping channelConfig = _config.getCvChannelMapping(midiChannel);

    if(channelConfig.from < channelConfig.to) {
        if(currentCvChannel == channelConfig.to) {
            _channelMapping[midiChannel] = channelConfig.from;
        } else {
            _channelMapping[midiChannel]++;
        }
    }
    
    return currentCvChannel;
}
