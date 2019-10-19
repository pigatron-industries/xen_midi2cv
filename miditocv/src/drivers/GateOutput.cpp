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

void GateOutput::setValue(uint8_t index, bool value) {
    _data[index] = value;
}


void GateOutput::sendData() {
    //start sequence
    digitalWrite(_latchPin, LOW);
    digitalWrite(_clockPin, LOW);

    for(uint8_t i = 0; i < _size; i++)
    {
        bool value = _data[i];

        digitalWrite(_dataPin, value);

        for(int j=15; j>=0; j--)
        {
            // Start with 1 = 00000001
            // Shift left j places = 00010000
            // And with value to isolate bit e.g. 00010000 & 01010101 = 00010000
            // Shift right j places = 00000001
            digitalWrite(_dataPin, ((value&(1<<j)))>>j);
            delayMicroseconds(CLOCKINTERVAL);
            digitalWrite(_clockPin, HIGH);
            delayMicroseconds(CLOCKINTERVAL);
            digitalWrite(_clockPin, LOW);
        }
    }

    //set latch
    digitalWrite(_dataPin, LOW);
    digitalWrite(_clockPin, LOW);
    digitalWrite(_latchPin, HIGH);
    delayMicroseconds(CLOCKINTERVAL);
    digitalWrite(_latchPin, LOW);
}
