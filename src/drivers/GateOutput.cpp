#include "GateOutput.h"

#include <Arduino.h>

GateOutput::GateOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size) :
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
    _data = new bool[_size];
    _triggerTimer = new Timer[_size];
    for(uint8_t i=0; i < _size; i++) {
        _data[i] = LOW;
        _triggerTimer[i] = Timer();
    }
    sendData();
}

void GateOutput::setValue(uint8_t index, bool value) {
    _data[index] = value;
}

void GateOutput::setTrigger(uint8_t index) {
    setValue(index, HIGH);
    _triggerTimer[index].start(TRIGGER_TIME);
}

void GateOutput::update() {
    for(uint8_t i=0; i < _size; i++) {
        if(_triggerTimer[i].hasJustStopped()) {
            setValue(i, LOW);
        }
    }
}

void GateOutput::sendData() {
    //start sequence
    digitalWrite(_latchPin, LOW);
    digitalWrite(_clockPin, LOW);

    for(int8_t i=_size-1; i>=0; i--) {
        digitalWrite(_dataPin, _data[i]);
        delayMicroseconds(CLOCKINTERVAL);
        digitalWrite(_clockPin, HIGH);
        delayMicroseconds(CLOCKINTERVAL);
        digitalWrite(_clockPin, LOW);
    }

    //set latch
    digitalWrite(_dataPin, LOW);
    digitalWrite(_clockPin, LOW);
    digitalWrite(_latchPin, HIGH);
    delayMicroseconds(CLOCKINTERVAL);
    digitalWrite(_latchPin, LOW);
}
