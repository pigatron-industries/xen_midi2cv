#include <Arduino.h>

#include "hwconfig.h"

#include "src/config/Configuration.h"
#include "src/drivers/StatusLed.h"
#include "src/drivers/pitchCvOutput.h"
#include "src/drivers/CvOutput.h"
#include "src/drivers/CvOutputService.h"
#include "src/processor/MidiEventProcessor.h"
#include "src/tasks/StatusLedTask.h"
#include "src/tasks/MidiInputTask.h"
#include "src/tasks/TriggerOutputTask.h"
#include "src/lib/TaskManager.h"


// hardware
GateOutput gateOutput = GateOutput(GATE_DATA_PIN, GATE_LATCH_PIN, GATE_CLOCK_PIN, CV_CHANNELS);
GateOutput triggerOutput = GateOutput(TRIG_DATA_PIN, TRIG_LATCH_PIN, TRIG_CLOCK_PIN, CV_CHANNELS);
PitchCvOutput pitchCvOutput = PitchCvOutput(PITCHCV_DATA_PIN, PITCHCV_LATCH_PIN, PITCHCV_CLOCK_PIN, CV_CHANNELS);
uint8_t cvSelectPins[CV_DEVICES] = CV_SELECT_PINS;
CvOutput cvOutput = CvOutput(new SPIClass(CV_MOSI_PIN, CV_MISO_PIN, CV_SCLK_PIN), CV_CNVT_PIN, cvSelectPins, CV_DEVICES);
StatusLed statusLed = StatusLed(LED_RED, LED_BLUE, LED_GREEN);

Configuration config = Configuration();

StatusLedTask statusLedTask = StatusLedTask(statusLed);
TriggerOutputTask triggerOutputTask = TriggerOutputTask(config, triggerOutput);

CvOutputService cvOutputService = CvOutputService(config, gateOutput,
                          triggerOutputTask, pitchCvOutput, cvOutput);

MidiToPitchConverter midiToPitchConverter = MidiToPitchConverter(config);
MidiEventProcessor midiEventProcessor = MidiEventProcessor(config, statusLedTask,
    cvOutputService, midiToPitchConverter);
MidiInputTask midiInputTask = MidiInputTask(midiEventProcessor);


void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("======================================");
    Serial.println("*     Pigatron Industries Midi2Cv    *");
    Serial.println("======================================");
    Serial.println();
    config.printConfig();

    Task* tasks[] = { &statusLedTask, &midiInputTask, &triggerOutputTask };
    TaskManager taskManager(tasks, 3);
    taskManager.run();
}
