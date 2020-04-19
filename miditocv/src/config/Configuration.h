#ifndef Configuration_h
#define Configuration_h

#include <inttypes.h>

#include "../protobuf/ConfigMessage.pb.h"


class Configuration {

public:
    Configuration();

    void printConfig();
    void resetDefault();
    void configUpdateMessage(uint8_t* encodedMessage, size_t size);

    /**
     * Returns an array of 2 channel numbers.
     * If the channels are the same then this designates a single channel mapping.
     * If they are different then it is a range of channels to rotate through.
     */
    xen_ChannelMapping* getCvChannelMapping(uint8_t midiChannel);
    xen_ControllerMapping* getCvControllerMapping(int8_t midiChannel, int8_t midiController);
    xen_PercussionMapping* getPercussionMapping(int8_t midiNote);
    xen_PercussionChannelConfig* getPercussionChannelConfig();

    float getNoteCents(int8_t note);
    float getOctaveCents();
    int8_t getNoteCount();

    unsigned long getTriggerTime();



private:

    xen_ConfigWrapper config;

    void defaultChannelConfig();
    void defaultControllerConfig();
    void defaultPercussionConfig();
    void defaultScale();

};

#endif
