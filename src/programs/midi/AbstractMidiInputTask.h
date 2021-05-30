#ifndef AbstractMidiInputTask_h
#define AbstractMidiInputTask_h

#include <inttypes.h>

#include "../../programs/midi/MidiEventProcessor.h"
#include "../../programs/midi/MidiOutputService.h"

#define SYSEX_BUFFER_SIZE 100

class AbstractMidiInputTask {

public:
    AbstractMidiInputTask(MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputService);

protected:
    MidiEventProcessor& midiEventProcessor;
    MidiOutputService& midiOutputService;
    uint8_t sysexBuffer[SYSEX_BUFFER_SIZE];
    uint8_t sysexBufferDecoded[SYSEX_BUFFER_SIZE];

    void handleMessage(uint8_t command, uint8_t channel, uint8_t data1, uint8_t data2);
    void handleControlChange(uint8_t midiChannel, int8_t controlNumber, int8_t msbValue, int8_t lsbValue);

private:
    int8_t prevCCChannel;
    int8_t prevCCControl;
    int8_t prevCCValue;

};

#endif
