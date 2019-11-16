#ifndef CvOutputService_h
#define CvOutputService_h

#include "src/config/Configuration.h"
#include "src/drivers/PitchCvOutput.h"
#include "src/drivers/GateOutput.h"
#include "src/drivers/CvOutput.h"
#include "src/tasks/TriggerOutputTask.h"
#include "src/lib/List.h"

#include <inttypes.h>

class CvOutputService {

public:
    CvOutputService(Configuration& config, GateOutput& gateOutput,
                    TriggerOutputTask& triggerOutputTask,
                    PitchCvOutput& pitchCvOutput, CvOutput& cvOutput);

    void setPitchValue(int8_t index, float value);
    void setGateValue(int8_t index, bool value);
    void setTrigger(int8_t index);
    void setControllerValue(int8_t index, float value);

private:
    Configuration& _config;
    GateOutput& _gateOutput;
    TriggerOutputTask& _triggerOutputTask;
    PitchCvOutput& _pitchCvOutput;
    CvOutput& _cvOutput;

};

#endif
