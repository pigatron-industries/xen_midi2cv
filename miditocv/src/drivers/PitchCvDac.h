#ifndef PitchCvDac_h
#define PitchCvDac_h

#include <inttypes.h>

#define CLOCKINTERVAL 0.5 //us

#define MIN_VALUE 0
#define MAX_VALUE 65535
#define MIN_VOLTAGE -10
#define MAX_VOLTAGE 10


class PitchCvDac {

public:
    PitchCvDac(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, int size);

    /**
     * Set a value of a single output. The actual output is not sent until a call to sendData is made.
     * @param index The index of the AD420 IC which the output is being set for.
     * @param value The value to set.
     */
    void setValue(int index, uint16_t value);

    void setVoltage(int index, float voltage);

    /**
     * Sends all data to the AD420 ICs.
     */
    void sendData();

private:
    uint8_t _dataPin;
    uint8_t _latchPin;
    uint8_t _clockPin;
    int _size;

    uint16_t* _data;

    float _factor;

};

#endif
