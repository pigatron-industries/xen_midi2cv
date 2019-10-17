#include "MidiEventProcessor.h"


MidiEventProcessor::MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, PitchCvOutput& pitchCvOutput) :
        _config(config),
        _statusLedTask(statusLedTask),
        _pitchCvOutput(pitchCvOutput) {
    _channelMapping = new uint8_t[_pitchCvOutput.getSize()];

    // default channel mappings
    for(uint8_t i = 0; i < _pitchCvOutput.getSize(); i++) {
        _channelMapping[i] = _config.getCvChannelMapping(i).from;
    }
}

void MidiEventProcessor::eventNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    _statusLedTask.blinkGreen();

    // convert midi channel to Pitch Cv Channel

    // convert note number to Pitch CV Ouput

    // convert velocity to Cv Ouput

    // send trigger and gate output
}

void MidiEventProcessor::eventNoteOff(uint8_t channel, uint8_t note) {
    _statusLedTask.blinkRed();

    // convert midi channel to Pitch Cv Channel

    // stop gate output
}
