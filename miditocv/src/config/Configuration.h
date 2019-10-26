#ifndef Configuration_h
#define Configuration_h

#include <inttypes.h>

#include "src/protobuf/ConfigMessage.pb.h"


struct ChannelMapping {
    uint8_t from;
    uint8_t to;
};


class Configuration {

public:
    Configuration();

    void resetDefault();
    void configUpdateMessage(uint8_t* encodedMessage, size_t size);

    /**
     * Returns an array of 2 channel numbers.
     * If the channels are the same then this designates a single channel mapping.
     * If they are different then it is a range of channels to rotate through.
     */
    ChannelMapping getCvChannelMapping(uint8_t midiChannel);


private:

    xen_WrapperMessage config;

};

#endif
