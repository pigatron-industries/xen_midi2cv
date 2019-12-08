
#include "CvOutput.h"


#define FACTOR (MAX_VALUE / (MAX_VOLTAGE - MIN_VOLTAGE))


CvOutput::CvOutput(SPIClass* spiClass, uint8_t convertPin, uint8_t* selectPins, uint8_t devices) :
        _spiClass(spiClass),
        _selectPins(selectPins),
        _convertPin(convertPin),
        _devices(devices) {
    _max11300 = new MAX11300*[devices];
    for(int i = 0; i < devices; i++) {
        //pinMode(selectPins[i], OUTPUT);
        _max11300[i] = new MAX11300(spiClass, convertPin, selectPins[i]);
        _max11300[i]->setPinMode(0, analogOut);
    }
}

void CvOutput::setValue(uint8_t index, uint16_t value) {

    _max11300[0]->setPinMode(0, analogOut);

    // double temp = _max11300[0]->readInternalTemp();
    // Serial.println(temp);


    pinMode_t pinMode = _max11300[0]->getPinMode(0);
    Serial.println(pinMode);
    //
    // value = 0x555;
    //
    // Serial.println("in");
    // Serial.println(value);
    // //
    // // //_max11300[0]->writeAnalogPin(0, value);
    // //
    // _max11300[0]->writeRegister(MAX_DACDAT_BASE, value);
    //
    // uint16_t out = _max11300[0]->readRegister(MAX_DACDAT_BASE);
    // //
    // Serial.println("out");
    // Serial.println(out);



    // TODO
}

void CvOutput::setVoltage(uint8_t index, float voltage) {
    Serial.println("cvOuptut::setVoltage");
    Serial.println(voltage);
    float absVoltage = voltage - MIN_VOLTAGE;
    float value = absVoltage * FACTOR;
    setValue(index, (uint16_t)value);
}
