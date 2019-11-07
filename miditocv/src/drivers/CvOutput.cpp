
#include "CvOutput.h"

#define MIN_VALUE 0
#define MAX_VALUE 4095
#define MAX_VOLTAGE_RANGE 10
#define FACTOR = (MAX_VALUE / VOLTAGE_RANGE)

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

void PitchCvOutput::setVoltage(uint8_t index, float voltage) {
    float value = voltage * FACTOR;
    setValue(index, (uint16_t)value);
}
