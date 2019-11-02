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
GateOutput gateOutput = GateOutput(GATE_DATA_PIN, GATE_LATCH_PIN, GATE_CLOCK_PIN, CV_CHANNELS);
PitchCvOutput pitchCvOutput = PitchCvOutput(PITCHCV_DATA_PIN, PITCHCV_LATCH_PIN, PITCHCV_CLOCK_PIN, CV_CHANNELS);
StatusLed statusLed = StatusLed(LED_RED, LED_BLUE, LED_GREEN);


StatusLedTask statusLedTask = StatusLedTask(statusLed);
Configuration config = Configuration();
MidiToPitchConverter midiToPitchConverter = MidiToPitchConverter(config);
MidiEventProcessor midiEventProcessor = MidiEventProcessor(config, statusLedTask, gateOutput, pitchCvOutput, midiToPitchConverter);
MidiInputTask midiInputTask = MidiInputTask(midiEventProcessor);


void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("======================================");
    Serial.println("*     Pigatron Industries Midi2Cv    *");
    Serial.println("======================================");
    Serial.println();
    config.printConfig();

    Task* tasks[] = { &statusLedTask, &midiInputTask };
    TaskManager taskManager(tasks, 2);
    taskManager.run();
}
