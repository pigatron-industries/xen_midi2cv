#ifndef CvOutputService_h
#define CvOutputService_h

#include "../config/Configuration.h"
#include "../lib/List.h"
#include "PitchCvOutput.h"
#include "GateOutput.h"
#include "CvOutput.h"

#include <inttypes.h>

class CvOutputService {

public:
    CvOutputService(Configuration& config, GateOutput& gateOutput,
                    PitchCvOutput& pitchCvOutput, CvOutput& cvOutput);
    void update();

    void setPitchValue(int8_t channel, float value);
    void setGateValue(int8_t channel, int8_t bank, bool value);
    void setTrigger(int8_t channel, int8_t bank);
    void setControlValue(int8_t channel, int8_t bank, float value);

private:
    Configuration& _config;
    GateOutput& _gateOutput;
    PitchCvOutput& _pitchCvOutput;
    CvOutput& _cvOutput;

    int8_t getIndex(int8_t channel, int8_t bank);

};

#endif
