#ifndef MidiInputTask_h
#define MidiInputTask_h

#include <inttypes.h>

#include "../../lib/Task.h"
#include "../../programs/midi/MidiEventProcessor.h"
#include "../../programs/midi/MidiOutputService.h"

#define SYSEX_BUFFER_SIZE 100
#define MESSAGE_BUFFER_SIZE 3

class MidiInputTask : public Task {

public:
    MidiInputTask(HardwareSerial& midiSerial, MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputSevice);
    void init();
    void execute();

private:
    HardwareSerial& _midiSerial;
    MidiEventProcessor& _midiEventProcessor;
    MidiOutputService& _midiOutputService;

    uint8_t sysexBuffer[SYSEX_BUFFER_SIZE];
    uint8_t sysexBufferDecoded[SYSEX_BUFFER_SIZE];

    int8_t prevCCChannel;
    int8_t prevCCControl;
    int8_t prevCCValue;

    uint8_t getByte();
    void handleControlChange(uint8_t midiChannel, int8_t controlNumber, int8_t msbValue, int8_t lsbValue);
    void handleSysex();
    void passThrough(byte byte);

};

#endif
