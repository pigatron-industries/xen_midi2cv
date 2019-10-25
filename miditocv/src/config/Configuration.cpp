#include "Configuration.h"


Configuration::Configuration() {
}


void Configuration::resetDefault() {
    //TODO
}


ChannelMapping Configuration::getCvChannelMapping(uint8_t midiChannel) {
    return ChannelMapping{midiChannel, midiChannel};
}
