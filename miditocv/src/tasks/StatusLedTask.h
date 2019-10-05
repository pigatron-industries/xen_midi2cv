#ifndef StatusLedTask_h
#define StatusLedTask_h

#include <inttypes.h>

#include "src/lib/Task.h"
#include "src/drivers/StatusLed.h"

#define BLINK_TIME 100000


class StatusLedTask : public Task {

public:
    StatusLedTask(StatusLed statusLed);
    void init();
    void execute();
    void blink();

private:
    StatusLed _statusLed;
    unsigned long blinkStartBlue;
    unsigned long blinkStartRed;
    unsigned long blinkStartGreen;

};

#endif
