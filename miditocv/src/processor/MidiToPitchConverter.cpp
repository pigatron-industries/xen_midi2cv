#include "MidiToPitchConverter.h"

#include <Arduino.h>
#include "math.h"


MidiToPitchConverter::MidiToPitchConverter(Configuration& config) :
        _config(config) {
}


float MidiToPitchConverter::convert(int8_t note, int8_t bend) {
    float octaveNum = floor(note / _config.getNoteCount());
    float noteNum = note - (octaveNum * _config.getNoteCount());
    float cents = octaveNum * _config.getOctaveCents() + _config.getNoteCents(noteNum);
    return cents / 1200;
}
