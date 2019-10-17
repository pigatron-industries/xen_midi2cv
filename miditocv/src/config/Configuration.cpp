#include "Configuration.h"


Configuration::Configuration() {
}


ChannelMapping Configuration::getCvChannelMapping(uint8_t midiChannel) {
    return ChannelMapping{midiChannel, midiChannel};
}
