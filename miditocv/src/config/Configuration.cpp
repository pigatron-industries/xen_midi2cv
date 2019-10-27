#include "Configuration.h"

#include <Arduino.h>

#include "src/lib/nanopb/pb_decode.h"
#include "src/hwconfig.h"



Configuration::Configuration() {
    resetDefault();
}


void Configuration::resetDefault() {
    config = xen_ConfigWrapper_init_zero;

    for(int i = 0; i < CV_CHANNELS; i++) {
        config.channelConfig.channelMapping[i].midiChannel = i;
        config.channelConfig.channelMapping[i].cvChannelFrom = i;
        config.channelConfig.channelMapping[i].cvChannelTo = i;
    }
    config.channelConfig.channelMapping_count = CV_CHANNELS;
}


xen_ChannelMapping* Configuration::getCvChannelMapping(uint8_t midiChannel) {
    for(int i = 0; i < config.channelConfig.channelMapping_count; i++) {
        if(config.channelConfig.channelMapping[i].midiChannel == midiChannel) {
            return &config.channelConfig.channelMapping[i];
        }
    }
    return NULL;
}


void Configuration::configUpdateMessage(uint8_t* encodedMessage, size_t size) {
    pb_istream_t stream = pb_istream_from_buffer(encodedMessage, size);
    bool status = pb_decode(&stream, xen_ConfigWrapper_fields, &config);
    if (!status) {
        Serial.println("Decoding config failed");
        Serial.println(PB_GET_ERROR(&stream));
        return;
    }

    printConfig();
}


void Configuration::printConfig() {
    Serial.println("System configured:");
    Serial.println();
    Serial.println("     Channel Mappings");
    for(int i = 0; i < config.channelConfig.channelMapping_count; i++) {
        Serial.print("          MIDI: ");
        Serial.print(config.channelConfig.channelMapping[i].midiChannel);
        Serial.print(" -> CV: ");
        Serial.print(config.channelConfig.channelMapping[i].cvChannelFrom);
        Serial.print(" - ");
        Serial.print(config.channelConfig.channelMapping[i].cvChannelTo);
        Serial.println();
    }
}
