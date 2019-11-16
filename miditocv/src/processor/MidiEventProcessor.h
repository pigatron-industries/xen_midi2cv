#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "src/config/Configuration.h"
#include "src/tasks/StatusLedTask.h"
#include "src/tasks/TriggerOutputTask.h"
#include "src/processor/CvOutputService.h"
#include "src/processor/MidiToPitchConverter.h"
#include "src/lib/List.h"

#include <inttypes.h>

class MidiEventProcessor {

public:
    MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask,
                       CvOutputService& cvOutputService,
                       MidiToPitchConverter& midiToPitchConverter);

    void eventNoteOn(uint8_t midiChannel, int8_t note, uint8_t velocity);
    void eventNoteOff(uint8_t midiChannel, int8_t note);
    void eventControlChange(uint8_t midiChannel, int8_t controlNumber, int8_t value);
    void eventNotePressure(uint8_t midiChannel, int8_t note, int8_t pressure);
    void eventPitchBend(uint8_t channel, int16_t bend);

    void eventSystemConfig(uint8_t* message, size_t size);

private:
    Configuration& _config;
    StatusLedTask& _statusLedTask;
    CvOutputService& _cvOutputService;
    MidiToPitchConverter _midiToPitchConverter;

    int8_t* _channelMapping; //midi channel -> cv channel
    float* _channelPitchBend; //midi channel -> pitch bend
    List* _channelNoteMapping; //cv channel -> note numbers currently held
    float* _channelNotePitch; //cv channek -> last output pitch

    void resetChannelMappings();
    int8_t getCvOutputChannel(int8_t midiChannel);
    int8_t getCvOutputChannelForNote(int8_t midiChannel, int8_t note);
    void saveNoteToChannel(int8_t cvChannel, int8_t note);
    bool clearNoteFromChannel(int8_t cvChannel, int8_t note);

};

#endif
