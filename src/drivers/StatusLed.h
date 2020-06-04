#ifndef StatusLed_h
#define StatusLed_h

#include <inttypes.h>

class StatusLed {

public:
    StatusLed(uint8_t redPin, uint8_t bluePin, uint8_t greenPin);

    void blueOn();
    void blueOff();
    void redOn();
    void redOff();
    void greenOn();
    void greenOff();

private:
    uint8_t _redPin;
    uint8_t _bluePin;
    uint8_t _greenPin;

};

#endif
