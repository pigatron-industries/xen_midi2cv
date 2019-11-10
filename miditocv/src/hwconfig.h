
// Hardware setup
#define GATE_DATA_PIN pinNametoDigitalPin(PD_7)
#define GATE_LATCH_PIN pinNametoDigitalPin(PD_6)
#define GATE_CLOCK_PIN pinNametoDigitalPin(PD_5)

#define TRIG_DATA_PIN pinNametoDigitalPin(PE_6)
#define TRIG_LATCH_PIN pinNametoDigitalPin(PE_3)
#define TRIG_CLOCK_PIN pinNametoDigitalPin(PE_8)

#define PITCHCV_DATA_PIN pinNametoDigitalPin(PE_2)
#define PITCHCV_CLOCK_PIN pinNametoDigitalPin(PE_4)
#define PITCHCV_LATCH_PIN pinNametoDigitalPin(PE_5)

#define CV_MOSI_PIN pinNametoDigitalPin(PF_2)
#define CV_MISO_PIN pinNametoDigitalPin(PF_1)
#define CV_SCLK_PIN pinNametoDigitalPin(PF_0)
#define CV_SELECT_PINS {pinNametoDigitalPin(PD_0), pinNametoDigitalPin(PD_1)}
#define CV_CNVT_PIN pinNametoDigitalPin(PG_0)

#define CV_CHANNELS 8
#define CV_DEVICES 2

#define MIDI_BAUD 31250
#define SERIAL_BAUD 115200
