#ifndef MidiToPitchConverter_h
#define MidiToPitchConverter_h

#include "src/config/Configuration.h"

#include <inttypes.h>

class MidiToPitchConverter {

public:
    MidiToPitchConverter(Configuration& config);

    float convertNote(int8_t note);
    float convertBend(int16_t bend);

private:
    Configuration& _config;

};


#endif
