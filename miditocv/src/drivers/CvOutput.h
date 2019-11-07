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
    CvOutput(SPIClass* spi, uint8_t convertPin, uint8_t* selectPins, uint8_t size);

private:
    MAX11300* _max11300;

};

#endif
