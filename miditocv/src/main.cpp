#include <Arduino.h>

#include "src/drivers/StatusLed.h"
#include "src/tasks/StatusLedTask.h"
#include "src/lib/TaskManager.h"


StatusLed statusLed = StatusLed(LED_RED, LED_BLUE, LED_GREEN);

StatusLedTask statusLedTask = StatusLedTask(statusLed);


void bootstrap() {
    Task* tasks[] = { &statusLedTask };
    TaskManager taskManager(tasks, 1);
    taskManager.run();
}
