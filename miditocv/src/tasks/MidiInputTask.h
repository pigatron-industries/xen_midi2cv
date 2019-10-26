#ifndef MidiInputTask_h
#define MidiInputTask_h

#include <inttypes.h>

#include "src/lib/Task.h"
#include "src/processor/MidiEventProcessor.h"

#define SYSEX_BUFFER_SIZE 100


class MidiInputTask : public Task {

public:
    MidiInputTask(MidiEventProcessor& midiEventProcessor);
    void init();
    void execute();

private:
    MidiEventProcessor& _midiEventProcessor;

    uint8_t sysexBuffer[SYSEX_BUFFER_SIZE];
    uint8_t sysexBufferDecoded[SYSEX_BUFFER_SIZE];

    uint8_t getByte();
    void handleSysex();

};

#endif
