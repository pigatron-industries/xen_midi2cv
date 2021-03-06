/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.4 at Sun Dec 29 22:00:28 2019. */

#ifndef PB_XEN_CONFIGMESSAGE_PB_H_INCLUDED
#define PB_XEN_CONFIGMESSAGE_PB_H_INCLUDED
#include "../lib/nanopb/pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _xen_ChannelMapping {
    int8_t midiChannel;
    int8_t cvChannelFrom;
    int8_t cvChannelTo;
/* @@protoc_insertion_point(struct:xen_ChannelMapping) */
} xen_ChannelMapping;

typedef struct _xen_ControllerMapping {
    int8_t midiChannel;
    int8_t midiController;
    int8_t cvChannel;
    int8_t cvBank;
/* @@protoc_insertion_point(struct:xen_ControllerMapping) */
} xen_ControllerMapping;

typedef struct _xen_PercussionMapping {
    int8_t midiNote;
    int8_t cvChannel;
    float control1Value;
    float control2Value;
/* @@protoc_insertion_point(struct:xen_PercussionMapping) */
} xen_PercussionMapping;

typedef struct _xen_Scale {
    pb_size_t cents_count;
    int32_t cents[48];
/* @@protoc_insertion_point(struct:xen_Scale) */
} xen_Scale;

typedef struct _xen_ChannelConfig {
    pb_size_t channelMapping_count;
    xen_ChannelMapping channelMapping[16];
/* @@protoc_insertion_point(struct:xen_ChannelConfig) */
} xen_ChannelConfig;

typedef struct _xen_ControllerConfig {
    pb_size_t controllerMapping_count;
    xen_ControllerMapping controllerMapping[32];
/* @@protoc_insertion_point(struct:xen_ControllerConfig) */
} xen_ControllerConfig;

typedef struct _xen_PercussionChannelConfig {
    int8_t midiChannel;
    pb_size_t percussionMapping_count;
    xen_PercussionMapping percussionMapping[64];
/* @@protoc_insertion_point(struct:xen_PercussionChannelConfig) */
} xen_PercussionChannelConfig;

typedef struct _xen_ConfigWrapper {
    bool has_channelConfig;
    xen_ChannelConfig channelConfig;
    bool has_scale;
    xen_Scale scale;
    bool has_triggerTime;
    int32_t triggerTime;
    bool has_controllerConfig;
    xen_ControllerConfig controllerConfig;
    bool has_percussionChannelConfig;
    xen_PercussionChannelConfig percussionChannelConfig;
/* @@protoc_insertion_point(struct:xen_ConfigWrapper) */
} xen_ConfigWrapper;

/* Default values for struct fields */

/* Initializer values for message structs */
#define xen_ConfigWrapper_init_default           {false, xen_ChannelConfig_init_default, false, xen_Scale_init_default, false, 0, false, xen_ControllerConfig_init_default, false, xen_PercussionChannelConfig_init_default}
#define xen_ChannelConfig_init_default           {0, {xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default, xen_ChannelMapping_init_default}}
#define xen_ChannelMapping_init_default          {0, 0, 0}
#define xen_ControllerConfig_init_default        {0, {xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default, xen_ControllerMapping_init_default}}
#define xen_ControllerMapping_init_default       {0, 0, 0, 0}
#define xen_PercussionChannelConfig_init_default {0, 0, {xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default, xen_PercussionMapping_init_default}}
#define xen_PercussionMapping_init_default       {0, 0, 0, 0}
#define xen_Scale_init_default                   {0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define xen_ConfigWrapper_init_zero              {false, xen_ChannelConfig_init_zero, false, xen_Scale_init_zero, false, 0, false, xen_ControllerConfig_init_zero, false, xen_PercussionChannelConfig_init_zero}
#define xen_ChannelConfig_init_zero              {0, {xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero, xen_ChannelMapping_init_zero}}
#define xen_ChannelMapping_init_zero             {0, 0, 0}
#define xen_ControllerConfig_init_zero           {0, {xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero, xen_ControllerMapping_init_zero}}
#define xen_ControllerMapping_init_zero          {0, 0, 0, 0}
#define xen_PercussionChannelConfig_init_zero    {0, 0, {xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero, xen_PercussionMapping_init_zero}}
#define xen_PercussionMapping_init_zero          {0, 0, 0, 0}
#define xen_Scale_init_zero                      {0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}

/* Field tags (for use in manual encoding/decoding) */
#define xen_ChannelMapping_midiChannel_tag       1
#define xen_ChannelMapping_cvChannelFrom_tag     2
#define xen_ChannelMapping_cvChannelTo_tag       3
#define xen_ControllerMapping_midiChannel_tag    1
#define xen_ControllerMapping_midiController_tag 2
#define xen_ControllerMapping_cvChannel_tag      4
#define xen_ControllerMapping_cvBank_tag         5
#define xen_PercussionMapping_midiNote_tag       1
#define xen_PercussionMapping_cvChannel_tag      2
#define xen_PercussionMapping_control1Value_tag  3
#define xen_PercussionMapping_control2Value_tag  4
#define xen_Scale_cents_tag                      1
#define xen_ChannelConfig_channelMapping_tag     1
#define xen_ControllerConfig_controllerMapping_tag 1
#define xen_PercussionChannelConfig_midiChannel_tag 1
#define xen_PercussionChannelConfig_percussionMapping_tag 2
#define xen_ConfigWrapper_channelConfig_tag      1
#define xen_ConfigWrapper_scale_tag              2
#define xen_ConfigWrapper_triggerTime_tag        3
#define xen_ConfigWrapper_controllerConfig_tag   4
#define xen_ConfigWrapper_percussionChannelConfig_tag 5

/* Struct field encoding specification for nanopb */
extern const pb_field_t xen_ConfigWrapper_fields[6];
extern const pb_field_t xen_ChannelConfig_fields[2];
extern const pb_field_t xen_ChannelMapping_fields[4];
extern const pb_field_t xen_ControllerConfig_fields[2];
extern const pb_field_t xen_ControllerMapping_fields[5];
extern const pb_field_t xen_PercussionChannelConfig_fields[3];
extern const pb_field_t xen_PercussionMapping_fields[5];
extern const pb_field_t xen_Scale_fields[2];

/* Maximum encoded size of messages (where known) */
#define xen_ConfigWrapper_size                   4770
#define xen_ChannelConfig_size                   560
#define xen_ChannelMapping_size                  33
#define xen_ControllerConfig_size                1472
#define xen_ControllerMapping_size               44
#define xen_PercussionChannelConfig_size         2187
#define xen_PercussionMapping_size               32
#define xen_Scale_size                           528

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define CONFIGMESSAGE_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
