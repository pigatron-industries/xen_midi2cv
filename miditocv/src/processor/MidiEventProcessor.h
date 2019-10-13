#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "src/drivers/PitchCvDac.h"
#include "src/tasks/StatusLedTask.h"

#include <Arduino.h>


class MidiEventProcessor {

public:
    MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvDac& pitchCvDac);

    void eventNoteOn(byte channel, byte note, byte velocity);
    void eventNoteOff(byte channel, byte note);

private:
    StatusLedTask& _statusLedTask;
    PitchCvDac& _pitchCvDac;

};

#endif
