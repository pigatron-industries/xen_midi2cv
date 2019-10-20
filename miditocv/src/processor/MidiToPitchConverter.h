#ifndef MidiToPitchConverter_h
#define MidiToPitchConverter_h

#include "src/config/Configuration.h"

#include <inttypes.h>

class MidiToPitchConverter {

public:
    MidiToPitchConverter(Configuration& config);

    float convert(int8_t note, int8_t bend);

private:
    Configuration _config;

};


#endif
