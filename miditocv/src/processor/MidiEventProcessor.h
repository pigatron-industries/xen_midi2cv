#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "src/config/Configuration.h"
#include "src/drivers/PitchCvOutput.h"
#include "src/tasks/StatusLedTask.h"

#include <Arduino.h>


class MidiEventProcessor {

public:
    MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, PitchCvOutput& pitchCvOutput);

    void eventNoteOn(uint8_t midiChannel, uint8_t note, uint8_t velocity);
    void eventNoteOff(uint8_t midiChannel, uint8_t note);

private:
    Configuration& _config;
    StatusLedTask& _statusLedTask;
    PitchCvOutput& _pitchCvOutput;

    uint8_t* _channelMapping;

    uint8_t getCvOutputChannel(uint8_t midiChannel);

};

#endif
