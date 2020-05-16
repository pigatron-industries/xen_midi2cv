#ifndef MidiEventProcessor_h
#define MidiEventProcessor_h

#include "../../config/Configuration.h"
#include "../../drivers/CvOutputService.h"
#include "../../programs/midi/MidiToPitchConverter.h"
#include "../../lib/List.h"
#include "../../hwconfig.h"

#include <inttypes.h>

#define MIDI_CHANNELS 16

class MidiEventProcessor {

public:
    MidiEventProcessor(Configuration& config,
                       CvOutputService& cvOutputService,
                       MidiToPitchConverter& midiToPitchConverter);

    void eventNoteOn(uint8_t midiChannel, int8_t note, uint8_t velocity);
    void eventNoteOff(uint8_t midiChannel, int8_t note);
    void eventControlChange(uint8_t midiChannel, int8_t controlNumber, int16_t value);
    void eventNotePressure(uint8_t midiChannel, int8_t note, int8_t pressure);
    void eventChannelPressure(uint8_t midiChannel, int8_t pressure);
    void eventPitchBend(uint8_t channel, int16_t bend);
    void eventClock();
    void eventStart();
    void eventStop();
    void eventReset();

    void eventSystemConfig(uint8_t* message, size_t size);

private:
    Configuration& _config;
    CvOutputService& _cvOutputService;
    MidiToPitchConverter _midiToPitchConverter;

    int8_t _channelMapping[MIDI_CHANNELS]; //midi channel -> cv channel
    float _channelPitchBend[MIDI_CHANNELS]; //midi channel -> pitch bend
    List _channelNoteMapping[CV_CHANNELS]; //cv channel -> note numbers currently held
    float _channelNotePitch[CV_CHANNELS]; //cv channel -> last output pitch
    uint8_t _clockCounter = 0;

    void resetChannelMappings();
    int8_t getCvOutputChannel(int8_t midiChannel);
    int8_t getCvOutputChannelForNote(int8_t midiChannel, int8_t note);
    void saveNoteToChannel(int8_t cvChannel, int8_t note);
    bool clearNoteFromChannel(int8_t cvChannel, int8_t note);

    void eventPercussionTrigger(int8_t note, uint8_t velocity);

};

#endif
