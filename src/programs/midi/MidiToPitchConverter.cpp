#include "MidiToPitchConverter.h"

#include <Arduino.h>
#include "math.h"

#define MAX_CONTROL_VOLTAGE 5


MidiToPitchConverter::MidiToPitchConverter(Configuration& config) :
        _config(config) {
}


float MidiToPitchConverter::convertNote(int8_t note) {
    float octaveNum = floor(note / _config.getNoteCount());
    float noteNum = note - (octaveNum * _config.getNoteCount());
    float cents = octaveNum * _config.getOctaveCents() + _config.getNoteCents(noteNum);
    return cents / 1200;
}

float MidiToPitchConverter::convertBend(int16_t bend) {
    return (float(bend) / 8192) / 12;
}

float MidiToPitchConverter::convertVelocity(uint8_t velocity) {
    return (float(velocity) / 127) * MAX_CONTROL_VOLTAGE;
}

float MidiToPitchConverter::convertControl(uint16_t value) {
    return (float(value) / 16384) * MAX_CONTROL_VOLTAGE;
}
