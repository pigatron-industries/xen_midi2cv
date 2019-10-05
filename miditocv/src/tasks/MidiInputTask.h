#ifndef MidiInputTask_h
#define MidiInputTask_h

#include <inttypes.h>

#include "src/lib/Task.h"
#include "src/tasks/StatusLedTask.h"

#define BLINK_TIME 100000


class MidiInputTask : public Task {

public:
    MidiInputTask(StatusLedTask statusLedTask);

private:
    StatusLedTask _statusLedTask;

};

#endif
