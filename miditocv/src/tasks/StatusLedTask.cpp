#include "StatusLedTask.h"

#include <Arduino.h>


StatusLedTask::StatusLedTask(StatusLed statusLed) :
    _statusLed(statusLed) {
}

void StatusLedTask::init() {
    Task::init();
    blinkBlue(); //blink for testing
}

void StatusLedTask::blinkBlue() {
    _statusLed.blueOn();
    blinkStartBlue = micros();
}

void StatusLedTask::blinkRed() {
    _statusLed.redOn();
    blinkStartRed = micros();
}

void StatusLedTask::blinkGreen() {
    _statusLed.greenOn();
    blinkStartGreen = micros();
}

void StatusLedTask::execute() {
    if (micros() - blinkStartBlue > BLINK_TIME) {
        _statusLed.blueOff();
    }
    if (micros() - blinkStartRed > BLINK_TIME) {
        _statusLed.redOff();
    }
    if (micros() - blinkStartGreen > BLINK_TIME) {
        _statusLed.greenOff();
    }
}
