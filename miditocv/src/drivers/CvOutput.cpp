
#include "CvOutput.h"


CvOutput::CvOutput(SPIClass* spi, uint8_t convertPin, uint8_t* selectPins, uint8_t devices) :
        _devices(devices) {
    for(int i = 0; i < devices; i++) {
        _max11300[i] = MAX11300(spi, convertPin, selectPins[i]);
        //TODO configure device
    }
}

void CvOutput::setValue(uint8_t index, uint16_t value) {
    // TODO
}
