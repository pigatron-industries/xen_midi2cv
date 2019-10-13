#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "src/drivers/pitchCvOutput.h"
#include "src/tasks/StatusLedTask.h"

#include <Arduino.h>


class MidiEventProcessor {

public:
    MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvOutput& pitchCvOutput);

    void eventNoteOn(byte channel, byte note, byte velocity);
    void eventNoteOff(byte channel, byte note);

private:
    StatusLedTask& _statusLedTask;
    PitchCvOutput& _pitchCvOutput;

};

#endif
