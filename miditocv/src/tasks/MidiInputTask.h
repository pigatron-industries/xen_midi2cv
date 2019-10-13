#ifndef MidiInputTask_h
#define MidiInputTask_h

#include <inttypes.h>

#include "src/lib/Task.h"
#include "src/processor/MidiEventProcessor.h"


class MidiInputTask : public Task {

public:
    MidiInputTask(MidiEventProcessor& midiEventProcessor);
    void init();
    void execute();

private:
    MidiEventProcessor& _midiEventProcessor;

};

#endif
