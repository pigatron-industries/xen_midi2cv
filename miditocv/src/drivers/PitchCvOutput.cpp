#include "PitchCvOutput.h"

#include <Arduino.h>

PitchCvOutput::PitchCvOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size) :
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
    _data = new uint16_t[_size];
    _factor = MAX_VALUE / (MAX_VOLTAGE - MIN_VOLTAGE);
}

void PitchCvOutput::setValue(int index, uint16_t value) {
    _data[index] = value;
}

void PitchCvOutput::setVoltage(int index, float voltage) {
    float absVoltage = voltage - MIN_VOLTAGE;
    float value = absVoltage * _factor;
    setValue(index, (int)value);
}

void PitchCvOutput::sendData() {
    //start sequence
    digitalWrite(_latchPin, LOW);
    digitalWrite(_clockPin, LOW);

    for(int i = 0; i < _size; i++)
    {
        uint16_t value = _data[i];

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
