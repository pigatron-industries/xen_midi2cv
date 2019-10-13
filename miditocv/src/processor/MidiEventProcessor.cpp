#include "MidiEventProcessor.h"


MidiEventProcessor::MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvDac& pitchCvDac) :
    _statusLedTask(statusLedTask),
    _pitchCvDac(pitchCvDac) {
}

void MidiEventProcessor::eventNoteOn() {
    _statusLedTask.blinkGreen();
}

void MidiEventProcessor::eventNoteOff() {
    _statusLedTask.blinkRed();
}
