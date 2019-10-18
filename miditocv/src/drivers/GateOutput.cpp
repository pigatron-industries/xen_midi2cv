#include "GateOutput.h"

#include <Arduino.h>

GateOutput::GateOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size) :
        _latchPin(latchPin),
        _clockPin(clockPin),
        _dataPin(dataPin),
        _size(size) {
    pinMode(_dataPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);
    digitalWrite(_latchPin, LOW);
    digitalWrite(_dataPin, LOW);
    _data = new bool[_size];
}
