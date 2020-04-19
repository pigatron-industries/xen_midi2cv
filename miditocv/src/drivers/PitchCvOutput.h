#ifndef PitchCvOutput_h
#define PitchCvOutput_h

#include <inttypes.h>

#define PITCH_MIN_VOLTAGE -10
#define PITCH_MAX_VOLTAGE 10

class PitchCvOutput {

public:
    PitchCvOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size);

    /**
     * Set a value of a single output. The actual output is not sent until a call to sendData is made.
     * @param index The index of the AD420 IC which the output is being set for.
     * @param value The value to set.
     */
    void setValue(uint8_t index, uint16_t value);

    void setVoltage(uint8_t index, float voltage);

    /**
     * Sends all data to the AD420 ICs.
     */
    void sendData();

    int getSize() { return _size; }

private:
    uint8_t _dataPin;
    uint8_t _latchPin;
    uint8_t _clockPin;
    uint8_t _size;

    uint16_t* _data;

};

#endif
