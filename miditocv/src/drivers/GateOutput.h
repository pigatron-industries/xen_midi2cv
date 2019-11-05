#ifndef GateOutput_h
#define GateOutput_h

#include <inttypes.h>

#define CLOCKINTERVAL 1 //us

class GateOutput {

public:
    GateOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size);

    void setValue(uint8_t index, bool value);
    void sendData();

    uint8_t getSize() { return _size; };
    bool* getData() { return _data; };

private:
    uint8_t _dataPin;
    uint8_t _latchPin;
    uint8_t _clockPin;
    uint8_t _size;

    bool* _data;

};

#endif
