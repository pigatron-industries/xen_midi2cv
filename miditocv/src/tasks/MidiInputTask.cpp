#include "MidiInputTask.h"

#include <Arduino.h>


MidiInputTask::MidiInputTask(StatusLedTask statusLedTask) :
    _statusLedTask(statusLedTask) {
}
