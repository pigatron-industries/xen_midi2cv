#include "StatusLedTask.h"

#include <Arduino.h>


StatusLedTask::StatusLedTask(StatusLed statusLed) :
    _statusLed(statusLed) {
}

void StatusLedTask::init() {
    Task::init();
    blink(); //blink for testing
}

void StatusLedTask::blink() {
    _statusLed.blueOn();
    blinkStart = micros();
}

void StatusLedTask::execute() {
    if (micros() - blinkStart > 100000) {
        _statusLed.blueOff();
        delay(1000);
        blink();   // blink again just for testing
    }
}
