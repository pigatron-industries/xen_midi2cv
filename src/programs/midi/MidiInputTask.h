#ifndef MidiInputTask_h
#define MidiInputTask_h

#include <inttypes.h>

#include "AbstractMidiInputTask.h"
#include "MidiEventProcessor.h"
#include "MidiOutputService.h"

class MidiInputTask : public AbstractMidiInputTask {

public:
    MidiInputTask(HardwareSerial& midiSerial, MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputSevice);
    void init();
    void execute();

private:
    HardwareSerial& _midiSerial;

    uint8_t getByte();
    void handleSysex();
    void passThrough(byte byte);

};

#endif
