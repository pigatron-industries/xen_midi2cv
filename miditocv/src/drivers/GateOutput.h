#ifndef GateOutput_h
#define GateOutput_h

#include <inttypes.h>

class GateOutput {

public:
    GateOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size);

private:
    uint8_t _dataPin;
    uint8_t _latchPin;
    uint8_t _clockPin;
    uint8_t _size;

    bool* _data;

};

#endif
