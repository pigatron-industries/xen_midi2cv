
// Hardware setup
#define GATE_DATA_PIN pinNametoDigitalPin(PD_7)
#define GATE_LATCH_PIN pinNametoDigitalPin(PD_6)
#define GATE_CLOCK_PIN pinNametoDigitalPin(PD_5)

#define TRIG_DATA_PIN pinNametoDigitalPin(PF_0)
#define TRIG_LATCH_PIN pinNametoDigitalPin(PF_1)
#define TRIG_CLOCK_PIN pinNametoDigitalPin(PF_2)

#define PITCHCV_DATA_PIN pinNametoDigitalPin(PF_8)
#define PITCHCV_CLOCK_PIN pinNametoDigitalPin(PF_7)
#define PITCHCV_LATCH_PIN pinNametoDigitalPin(PF_9)


#define CV_MOSI_PIN pinNametoDigitalPin(PA_7)
#define CV_MISO_PIN pinNametoDigitalPin(PA_6)
#define CV_SCLK_PIN pinNametoDigitalPin(PA_5)
#define CV_SELECT_PINS {pinNametoDigitalPin(PD_14), pinNametoDigitalPin(PD_15)}
#define CV_CNVT_PIN pinNametoDigitalPin(PF_12)

#define CV_CHANNELS 8
#define CV_DEVICES 2
#define CV_CONTROLS 40
#define TRIGGER_CONTROLS 16

#define MIDI_BAUD 31250
#define SERIAL_BAUD 115200
