#include "CvOutputService.h"

#include "src/hwconfig.h"

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


void CvOutputService::setTrigger(int8_t channel, int8_t bank) {
    _triggerOutputTask.trigger(getIndex(channel, bank));
}


void CvOutputService::setControlValue(int8_t channel, int8_t bank, float value) {
    _cvOutput.setVoltage(getIndex(channel, bank), value);
}

int8_t CvOutputService::getIndex(int8_t channel, int8_t bank) {
    return (bank * CV_CHANNELS) + channel;
}
