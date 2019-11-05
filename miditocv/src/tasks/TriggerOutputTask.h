#ifndef TriggerOutputTask_h
#define TriggerOutputTask_h

#include <inttypes.h>

#include "src/lib/Task.h"
#include "src/drivers/GateOutput.h"
#include "src/config/Configuration.h"


class TriggerOutputTask : public Task {

public:
    TriggerOutputTask(Configuration& config, GateOutput& gateOutput);
    void init();
    void execute();

    void trigger(uint8_t index);
    void sendData();

private:
    Configuration& _config;
    GateOutput& _gateOutput;

    unsigned long* _triggerTimes;

};

#endif
