#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "src/config/Configuration.h"
#include "src/drivers/PitchCvOutput.h"
#include "src/drivers/GateOutput.h"
#include "src/tasks/StatusLedTask.h"
#include "src/processor/MidiToPitchConverter.h"
#include "src/lib/List.h"

#include <inttypes.h>

class MidiEventProcessor {

public:
    MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, GateOutput& gateOutput, PitchCvOutput& pitchCvOutput,
                       MidiToPitchConverter& midiToPitchConverter);

    void eventNoteOn(uint8_t midiChannel, int8_t note, uint8_t velocity);
    void eventNoteOff(uint8_t midiChannel, int8_t note);

private:
    Configuration& _config;
    StatusLedTask& _statusLedTask;
    GateOutput& _gateOutput;
    PitchCvOutput& _pitchCvOutput;
    MidiToPitchConverter _midiToPitchConverter;

    uint8_t* _channelMapping; //midi channel -> cv channel
    List* _channelNoteMapping; //cv channel -> note numbers

    uint8_t getCvOutputChannel(uint8_t midiChannel);
    uint8_t getCvOutputChannelForNote(uint8_t midiChannel, uint8_t note);
    void saveNoteToChannel(uint8_t cvChannel, uint8_t note);
    bool clearNoteFromChannel(uint8_t cvChannel, uint8_t note);

};

#endif
