#include "MidiEventProcessor.h"


MidiEventProcessor::MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvOutput& pitchCvOutput) :
    _statusLedTask(statusLedTask),
    _pitchCvOutput(pitchCvOutput) {
}

void MidiEventProcessor::eventNoteOn(byte channel, byte note, byte velocity) {
    _statusLedTask.blinkGreen();
}

void MidiEventProcessor::eventNoteOff(byte channel, byte note) {
    _statusLedTask.blinkRed();
}
