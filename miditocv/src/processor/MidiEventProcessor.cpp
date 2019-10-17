#include "MidiEventProcessor.h"


MidiEventProcessor::MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvOutput& pitchCvOutput) :
    _statusLedTask(statusLedTask),
    _pitchCvOutput(pitchCvOutput) {
      _channelMapping = new uint8_t[_pitchCvOutput.getSize()];
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
