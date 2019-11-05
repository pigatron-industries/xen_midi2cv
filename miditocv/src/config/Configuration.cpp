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

    config.scale.cents_count = 12;
    config.scale.cents[0] = 100;
    config.scale.cents[1] = 200;
    config.scale.cents[2] = 300;
    config.scale.cents[3] = 400;
    config.scale.cents[4] = 500;
    config.scale.cents[5] = 600;
    config.scale.cents[6] = 700;
    config.scale.cents[7] = 800;
    config.scale.cents[8] = 900;
    config.scale.cents[9] = 1000;
    config.scale.cents[10] = 1100;
    config.scale.cents[11] = 1200;

    config.triggerTime = 5000;
}


xen_ChannelMapping* Configuration::getCvChannelMapping(uint8_t midiChannel) {
    for(int i = 0; i < config.channelConfig.channelMapping_count; i++) {
        if(config.channelConfig.channelMapping[i].midiChannel == midiChannel) {
            return &config.channelConfig.channelMapping[i];
        }
    }
    return NULL;
}


float Configuration::getNoteCents(int8_t noteNum) {
    if(noteNum == 0) {
        return 0;
    } else {
        return config.scale.cents[noteNum-1];
    }
}


float Configuration::getOctaveCents() {
    return config.scale.cents[config.scale.cents_count-1];
}


int8_t Configuration::getNoteCount() {
    return config.scale.cents_count;
}


void Configuration::configUpdateMessage(uint8_t* encodedMessage, size_t size) {
    xen_ConfigWrapper configMessage = xen_ConfigWrapper_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(encodedMessage, size);
    bool status = pb_decode(&stream, xen_ConfigWrapper_fields, &configMessage);
    if (!status) {
        Serial.println("Decoding config failed");
        Serial.println(PB_GET_ERROR(&stream));
        return;
    }

    if(configMessage.has_channelConfig) {
        config.channelConfig = configMessage.channelConfig;
    }

    if(configMessage.has_scale) {
        config.scale = configMessage.scale;
    }

    if(configMessage.has_triggerTime) {
        config.triggerTime = configMessage.triggerTime;
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

    Serial.println();
    Serial.println("     Scale");
    Serial.print("          Notes/octave: ");
    Serial.println(getNoteCount());
    Serial.print("          Octave size: ");
    Serial.println(getOctaveCents());
    for(int i = 0; i < config.scale.cents_count; i++) {
        Serial.print("          ");
        Serial.print(i);
        Serial.print(" -> ");
        Serial.print(getNoteCents(i));
        Serial.println();
    }

    Serial.println();
}

unsigned long Configuration::getTriggerTime() {
    return config.triggerTime;
}
