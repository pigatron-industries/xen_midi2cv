#include "StatusLed.h"

#include <Arduino.h>

StatusLed::StatusLed(uint8_t redPin, uint8_t bluePin, uint8_t greenPin) {
    _redPin = redPin;
    _bluePin = bluePin;
    _greenPin = greenPin;
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

void StatusLed::blueOn() {
    digitalWrite(_bluePin, HIGH);
}

void StatusLed::blueOff() {
    digitalWrite(_bluePin, LOW);
}

void StatusLed::redOn() {
    digitalWrite(_redPin, HIGH);
}

void StatusLed::redOff() {
    digitalWrite(_redPin, LOW);
}

void StatusLed::greenOn() {
    digitalWrite(_greenPin, HIGH);
}

void StatusLed::greenOff() {
    digitalWrite(_greenPin, LOW);
}
