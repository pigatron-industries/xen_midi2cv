#ifndef StatusLedTask_h
#define StatusLedTask_h

#include <inttypes.h>

#include "src/lib/Task.h"
#include "src/drivers/StatusLed.h"

class StatusLedTask : public Task {

public:
    StatusLedTask(StatusLed statusLed);
    void init();
    void execute();
    void blink();

private:
    StatusLed _statusLed;
    unsigned long blinkStart;

};

#endif
