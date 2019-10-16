#include "MidiEventProcessor.h"


MidiEventProcessor::MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvOutput& pitchCvOutput) :
    _statusLedTask(statusLedTask),
    _pitchCvOutput(pitchCvOutput) {
}

void MidiEventProcessor::eventNoteOn(byte channel, byte note, byte velocity) {
    _statusLedTask.blinkGreen();

    // convert midi channel to Pitch Cv Channel

    // convert note number to Pitch CV Ouput

    // convert velocity to Cv Ouput

    // send trigger and gate output
}

void MidiEventProcessor::eventNoteOff(byte channel, byte note) {
    _statusLedTask.blinkRed();

    // convert midi channel to Pitch Cv Channel

    // stop gate output
}
