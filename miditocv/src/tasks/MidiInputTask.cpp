#include "MidiInputTask.h"

#include <Arduino.h>


MidiInputTask::MidiInputTask(StatusLedTask statusLedTask) :
    _statusLedTask(statusLedTask) {
}

void MidiInputTask::init() {
    Task::init();
}

void MidiInputTask::execute() {
    Serial.println("Hello world");
}
