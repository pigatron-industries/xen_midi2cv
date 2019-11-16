#include "CvOutputService.h"


CvOutputService::CvOutputService(Configuration& config, GateOutput& gateOutput,
                                 TriggerOutputTask& triggerOutputTask,
                                 PitchCvOutput& pitchCvOutput, CvOutput& cvOutput) :
        _config(config),
        _gateOutput(gateOutput),
        _triggerOutputTask(triggerOutputTask),
        _pitchCvOutput(pitchCvOutput),
        _cvOutput(cvOutput) {
}


void CvOutputService::setPitchValue(int8_t index, float value) {
    _pitchCvOutput.setVoltage(index, value);
    _pitchCvOutput.sendData();
}


void CvOutputService::setGateValue(int8_t index, bool value) {
    _gateOutput.setValue(index, value);
    _gateOutput.sendData();
}


void CvOutputService::setTrigger(int8_t index) {
    _triggerOutputTask.trigger(index);
}


void CvOutputService::setControllerValue(int8_t index, float value) {
    _cvOutput.setVoltage(index, value);
}
