#include "PitchCvOutput.h"

#include <Arduino.h>

#define CLOCKINTERVAL 0.5 //us

#define MIN_VALUE 0
#define MAX_VALUE 65535
#define FACTOR (MAX_VALUE / (PITCH_MAX_VOLTAGE - PITCH_MIN_VOLTAGE))

PitchCvOutput::PitchCvOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size) :
        _dataPin(dataPin),
        _latchPin(latchPin),
        _clockPin(clockPin),
        _size(size) {
    pinMode(_dataPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);
    digitalWrite(_latchPin, LOW);
    digitalWrite(_dataPin, LOW);
    _data = new uint16_t[_size];
}

void PitchCvOutput::setValue(uint8_t index, uint16_t value) {
    _data[index] = value;
}

void PitchCvOutput::setVoltage(uint8_t index, float voltage) {
    float absVoltage = voltage - PITCH_MIN_VOLTAGE;
    float value = absVoltage * FACTOR;
    setValue(index, (uint16_t)value);
}

void PitchCvOutput::sendData() {
    //start sequence
    digitalWrite(_latchPin, LOW);
    digitalWrite(_clockPin, LOW);

    for(int8_t i=_size-1; i>=0; i--) {
        uint16_t value = _data[i];

        for(int8_t j=15; j>=0; j--) {
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
