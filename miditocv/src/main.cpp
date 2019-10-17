#include <Arduino.h>

#include "hwconfig.h"

#include "src/config/Configuration.h"
#include "src/drivers/StatusLed.h"
#include "src/drivers/pitchCvOutput.h"
#include "src/processor/MidiEventProcessor.h"
#include "src/tasks/StatusLedTask.h"
#include "src/tasks/MidiInputTask.h"
#include "src/lib/TaskManager.h"


// hardware
PitchCvOutput pitchCvOutput = PitchCvOutput(PITCHCV_DATA_PIN, PITCHCV_LATCH_PIN, PITCHCV_CLOCK_PIN, PITCHCV_CHANNELS);
StatusLed statusLed = StatusLed(LED_RED, LED_BLUE, LED_GREEN);


StatusLedTask statusLedTask = StatusLedTask(statusLed);
Configuration config = Configuration();
MidiEventProcessor midiEventProcessor = MidiEventProcessor(config, statusLedTask, pitchCvOutput);
MidiInputTask midiInputTask = MidiInputTask(midiEventProcessor);


void bootstrap() {
    Serial.begin(115200);

    Task* tasks[] = { &statusLedTask, &midiInputTask };
    TaskManager taskManager(tasks, 2);
    taskManager.run();
}
