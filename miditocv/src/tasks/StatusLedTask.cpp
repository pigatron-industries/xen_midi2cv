#include "StatusLedTask.h"

#include <Arduino.h>


StatusLedTask::StatusLedTask(StatusLed& statusLed) :
    _statusLed(statusLed) {
}

void StatusLedTask::init() {
    Task::init();
    blinkBlue(); //blink for testing
}

void StatusLedTask::blinkBlue() {
    _statusLed.blueOn();
    blinkStartBlue = millis();
}

void StatusLedTask::blinkRed() {
    _statusLed.redOn();
    blinkStartRed = millis();
}

void StatusLedTask::blinkGreen() {
    _statusLed.greenOn();
    blinkStartGreen = millis();
}

void StatusLedTask::execute() {
    if (millis() - blinkStartBlue > BLINK_TIME) {
        _statusLed.blueOff();
    }
    if (millis() - blinkStartRed > BLINK_TIME) {
        _statusLed.redOff();
    }
    if (millis() - blinkStartGreen > BLINK_TIME) {
        _statusLed.greenOff();
    }
}
