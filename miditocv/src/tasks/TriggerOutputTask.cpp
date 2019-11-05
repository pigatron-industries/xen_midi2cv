#include "TriggerOutputTask.h"

#include <Arduino.h>


TriggerOutputTask::TriggerOutputTask(Configuration& config, GateOutput& gateOutput) :
    _config(config),
    _gateOutput(gateOutput) {
      _triggerTimes = new unsigned long[gateOutput.getSize()];
}

void TriggerOutputTask::init() {
    Task::init();
}

void TriggerOutputTask::execute() {
    for(uint8_t i = 0; i < _gateOutput.getSize(); i++) {
        if(_gateOutput.getData()[i]) {
            unsigned long elapsedTime = micros() - _triggerTimes[i];
            if(elapsedTime > _config.getTriggerTime()) {
                _gateOutput.setValue(i, LOW);
            }
        }
    }
    _gateOutput.sendData();
}

void TriggerOutputTask::trigger(uint8_t index) {
    _gateOutput.setValue(index, HIGH);
    _triggerTimes[index] = micros();
}

void TriggerOutputTask::sendData() {
    _gateOutput.sendData();
}
