#include "MidiEventProcessor.h"

#include <Arduino.h>


MidiEventProcessor::MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvDac& pitchCvDac) :
    _statusLedTask(statusLedTask),
    _pitchCvDac(pitchCvDac) {
}

void MidiEventProcessor::eventNoteOn(byte channel, byte note, byte velocity) {
    _statusLedTask.blinkGreen();
}

void MidiEventProcessor::eventNoteOff(byte channel, byte note) {
    _statusLedTask.blinkRed();
}
