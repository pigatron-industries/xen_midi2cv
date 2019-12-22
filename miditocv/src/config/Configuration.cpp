#include "Configuration.h"

#include <Arduino.h>

#include "src/lib/nanopb/pb_decode.h"
#include "src/hwconfig.h"



Configuration::Configuration() {
    resetDefault();
}


xen_ChannelMapping* Configuration::getCvChannelMapping(uint8_t midiChannel) {
    for(int i = 0; i < config.channelConfig.channelMapping_count; i++) {
        if(config.channelConfig.channelMapping[i].midiChannel == midiChannel) {
            return &config.channelConfig.channelMapping[i];
        }
    }
    return NULL;
}


xen_ControllerMapping* Configuration::getCvControllerMapping(int8_t midiChannel, int8_t midiController) {
    for(int i = 0; i < config.controllerConfig.controllerMapping_count; i++) {
        if(config.controllerConfig.controllerMapping[i].midiChannel == midiChannel &&
          config.controllerConfig.controllerMapping[i].midiController == midiController) {
              return &config.controllerConfig.controllerMapping[i];
        }
    }
    return NULL;
}


xen_PercussionChannelConfig* Configuration::getPercussionChannelConfig() {
    return &config.percussionChannelConfig;
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

    if(configMessage.has_controllerConfig) {
        config.controllerConfig = configMessage.controllerConfig;
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


/******************************************************************************
 *                          Default Configuration                             *
 ******************************************************************************/

void Configuration::resetDefault() {
    config = xen_ConfigWrapper_init_zero;
    defaultChannelConfig();
    defaultPercussionConfig();
    defaultControllerConfig();
    defaultScale();
    config.triggerTime = 5000;
}


void Configuration::defaultChannelConfig() {
    for(int cvChannel = 0; cvChannel < CV_CHANNELS; cvChannel++) {
        config.channelConfig.channelMapping[cvChannel].midiChannel = cvChannel;
        config.channelConfig.channelMapping[cvChannel].cvChannelFrom = cvChannel;
        config.channelConfig.channelMapping[cvChannel].cvChannelTo = cvChannel;
    }
    config.channelConfig.channelMapping_count = CV_CHANNELS;
}


void Configuration::defaultControllerConfig() {
    int cvIndex = 0;
    // note bank 1
    for(int cvChannel = 0; cvChannel < CV_CHANNELS; cvChannel++) {
        config.controllerConfig.controllerMapping[cvIndex].midiChannel = cvChannel;
        config.controllerConfig.controllerMapping[cvIndex].midiController = 1;
        config.controllerConfig.controllerMapping[cvIndex].cvChannel = cvChannel;
        config.controllerConfig.controllerMapping[cvIndex].cvBank = 1;
        cvIndex++;
    }
    // note bank 2
    for(int cvChannel = 0; cvChannel < CV_CHANNELS; cvChannel++) {
        config.controllerConfig.controllerMapping[cvIndex].midiChannel = cvChannel;
        config.controllerConfig.controllerMapping[cvIndex].midiController = 2;
        config.controllerConfig.controllerMapping[cvIndex].cvChannel = cvChannel;
        config.controllerConfig.controllerMapping[cvIndex].cvBank = 2;
        cvIndex++;
    }
    // percussion bank 4
    for(int cvChannel = 0; cvChannel < CV_CHANNELS; cvChannel++) {
        config.controllerConfig.controllerMapping[cvIndex].midiChannel = config.percussionChannelConfig.midiChannel;
        config.controllerConfig.controllerMapping[cvIndex].midiController = cvChannel+1;
        config.controllerConfig.controllerMapping[cvIndex].cvChannel = cvChannel;
        config.controllerConfig.controllerMapping[cvIndex].cvBank = 4;
        cvIndex++;
    }
    config.controllerConfig.controllerMapping_count = cvIndex;
}


void Configuration::defaultPercussionConfig() {
    config.percussionChannelConfig.midiChannel = 9;
    for(int note = 0; note < CV_CHANNELS; note++) {
        config.percussionChannelConfig.midiNotes[note] = note+1; //TODO suitable defualts for midi notes
    }
    config.percussionChannelConfig.midiNotes_count = CV_CHANNELS;
}


void Configuration::defaultScale() {
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
}
