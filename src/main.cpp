#include <Arduino.h>

#include "hwconfig.h"

#include "config/Configuration.h"
#include "drivers/pitchCvOutput.h"
#include "drivers/CvOutput.h"
#include "drivers/CvOutputService.h"
#include "programs/OutputUpdateTask.h"
#include "programs/midi/MidiEventProcessor.h"
#include "programs/midi/MidiInputTask.h"
#include "programs/midi/MidiOutputService.h"
#include "lib/TaskManager.h"


// hardware
GateOutput gateOutput = GateOutput(GATE_DATA_PIN, GATE_LATCH_PIN, GATE_CLOCK_PIN, CV_CHANNELS*GATE_BANKS);
PitchCvOutput pitchCvOutput = PitchCvOutput(PITCHCV_DATA_PIN, PITCHCV_LATCH_PIN, PITCHCV_CLOCK_PIN, CV_CHANNELS);
uint8_t cvSelectPins[CV_DEVICES] = CV_SELECT_PINS;
CvOutput cvOutput = CvOutput(&SPI, CV_CNVT_PIN, cvSelectPins, CV_DEVICES);

Configuration config = Configuration();

CvOutputService cvOutputService = CvOutputService(config, gateOutput, pitchCvOutput, cvOutput);

MidiToPitchConverter midiToPitchConverter = MidiToPitchConverter(config);
MidiEventProcessor midiEventProcessor = MidiEventProcessor(config, cvOutputService, midiToPitchConverter);
MidiOutputService midiOutputSevice = MidiOutputService(Serial2);
MidiInputTask midiInputTask1 = MidiInputTask(Serial1, midiEventProcessor, midiOutputSevice);
MidiInputTask midiInputTask2 = MidiInputTask(Serial2, midiEventProcessor, midiOutputSevice);
MidiInputTask midiInputTask3 = MidiInputTask(Serial3, midiEventProcessor, midiOutputSevice);
OutputUpdateTask outputUpdateTask = OutputUpdateTask(cvOutputService);

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("======================================");
    Serial.println("*     Pigatron Industries Midi2Cv    *");
    Serial.println("======================================");
    Serial.println();
    config.printConfig();

    midiInputTask1.init();
    midiInputTask2.init();
    midiInputTask3.init();
    outputUpdateTask.init();
}

void loop() {
    midiInputTask1.execute();
    midiInputTask2.execute();
    midiInputTask3.execute();
    outputUpdateTask.execute();
}
