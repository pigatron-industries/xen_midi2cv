#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "src/drivers/PitchCvDac.h"
#include "src/tasks/StatusLedTask.h"


class MidiEventProcessor {

public:
    MidiEventProcessor(StatusLedTask& statusLedTask, PitchCvDac& pitchCvDac);

    void eventNoteOn();
    void eventNoteOff();

private:
    StatusLedTask& _statusLedTask;
    PitchCvDac& _pitchCvDac;

};

#endif
