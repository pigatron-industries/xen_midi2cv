#ifndef CvOutput_h
#define CvOutput_h

#include <inttypes.h>
#include "src/lib/max11300/MAX11300.h"

class CvOutput {

public:
    /**
     * spi - class which defines spi pins MISO, MOSI, CLK
     * convertPin - pin attached to CNVT pin on all devices.
     * selectPins - list of pins connected to select each MAX11300 device.
     * size - Number of MAX11300 dvices connected.
     */
    CvOutput(SPIClass* spi, uint8_t convertPin, uint8_t* selectPins, uint8_t devices);

    /**
     * Only uses the first 12-bits of value to set the output.
     */
    void setValue(uint8_t index, uint16_t value);

    /**
     * Voltage can be 0 to 10.
     * Depending on actual pin configuration this could be
     * mapped to voltage ranges -10v>0v -5v>5v 0v>10v
     */
    void setVoltage(uint8_t index, float voltage);

private:
    MAX11300* _max11300;
    uint8_t _devices;

};

#endif
