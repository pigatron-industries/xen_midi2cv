
#include "CvOutput.h"


CvOutput::CvOutput(SPIClass* spi, uint8_t convertPin, uint8_t* selectPins, uint8_t size) {
    for(int i = 0; i < size; i++) {
        _max11300[i] = MAX11300(spi, convertPin, selectPins[i]);
    }
}
