#include <Arduino.h>

#include "src/drivers/StatusLed.h"
#include "src/drivers/pitchCvOutput.h"
#include "src/processor/MidiEventProcessor.h"
#include "src/tasks/StatusLedTask.h"
#include "src/tasks/MidiInputTask.h"
#include "src/lib/TaskManager.h"


// Hardware setup
#define PITCHCV_DATA_PIN pinNametoDigitalPin(PC_0)
#define PITCHCV_LATCH_PIN pinNametoDigitalPin(PC_3)
#define PITCHCV_CLOCK_PIN pinNametoDigitalPin(PC_1)
#define PITCHCV_CHANNELS 1


PitchCvOutput pitchCvOutput = PitchCvOutput(PITCHCV_DATA_PIN, PITCHCV_LATCH_PIN, PITCHCV_CLOCK_PIN, PITCHCV_CHANNELS);
StatusLed statusLed = StatusLed(LED_RED, LED_BLUE, LED_GREEN);


StatusLedTask statusLedTask = StatusLedTask(statusLed);


MidiEventProcessor midiEventProcessor = MidiEventProcessor(statusLedTask, pitchCvOutput);
MidiInputTask midiInputTask = MidiInputTask(midiEventProcessor);


void bootstrap() {
    Serial.begin(115200);

    Task* tasks[] = { &statusLedTask, &midiInputTask };
    TaskManager taskManager(tasks, 2);
    taskManager.run();
}
