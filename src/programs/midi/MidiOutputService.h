#ifndef MidiOutputService_h
#define MidiOutputService_h

#include <inttypes.h>
#include <Arduino.h>


class MidiOutputService {

public:
    MidiOutputService(HardwareSerial& _midiSerial1, HardwareSerial& _midiSerial2);

    void sendMessage(uint8_t* buf, uint8_t length);
    void sendByte(uint8_t byte);

private:
    HardwareSerial& midiSerial1;
    HardwareSerial& midiSerial2;

};

#endif
