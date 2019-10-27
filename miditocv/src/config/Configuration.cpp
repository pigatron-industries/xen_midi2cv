#include "Configuration.h"

#include <Arduino.h>

#include "src/lib/nanopb/pb_decode.h"



Configuration::Configuration() {
}


void Configuration::resetDefault() {
    //TODO
}


ChannelMapping Configuration::getCvChannelMapping(uint8_t midiChannel) {
    return ChannelMapping{midiChannel, midiChannel};
}


void Configuration::configUpdateMessage(uint8_t* encodedMessage, size_t size) {
    xen_ConfigWrapper wrapper = xen_ConfigWrapper_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(encodedMessage, size);
    bool status = pb_decode(&stream, xen_ConfigWrapper_fields, &wrapper);

    if (!status) {
        Serial.println("Decoding config failed");
        Serial.println(PB_GET_ERROR(&stream));
        return;
    }

    Serial.println(wrapper.channelConfig.channelMapping[0].midiChannel);
}
