#include "MidiToPitchConverter.h"

#include "math.h"

#define SCALE_NOTESPEROCTAVE 12
#define SCALE_OCTAVECENTS 1200
#define SCALE_NOTECENTS 100

MidiToPitchConverter::MidiToPitchConverter(Configuration& config) :
        _config(config) {
}


float MidiToPitchConverter::convert(int8_t note, int8_t bend) {
    float octaveNum = floor(note / SCALE_NOTESPEROCTAVE);
    float noteNum = note - (octaveNum * SCALE_NOTESPEROCTAVE);
    float cents = octaveNum * SCALE_OCTAVECENTS + (noteNum * SCALE_NOTECENTS);
    return cents / 1200;
}
