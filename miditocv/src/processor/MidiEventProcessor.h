#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "src/config/Configuration.h"
#include "src/drivers/PitchCvOutput.h"
#include "src/drivers/GateOutput.h"
#include "src/tasks/StatusLedTask.h"

#include <Arduino.h>


class MidiEventProcessor {

public:
    MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, GateOutput& gateOutput, PitchCvOutput& pitchCvOutput);

    void eventNoteOn(uint8_t midiChannel, uint8_t note, uint8_t velocity);
    void eventNoteOff(uint8_t midiChannel, uint8_t note);

private:
    Configuration& _config;
    StatusLedTask& _statusLedTask;
    GateOutput& _gateOutput;
    PitchCvOutput& _pitchCvOutput;

    uint8_t* _channelMapping; //midi channel -> cv channel
    uint8_t* _lastNoteChannel; //cv channel -> note number

    uint8_t getCvOutputChannel(uint8_t midiChannel);
    uint8_t getCvOutputChannel(uint8_t midiChannel, uint8_t note);

};

#endif
