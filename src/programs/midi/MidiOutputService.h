#ifndef MidiOutputService_h
#define MidiOutputService_h

#include <inttypes.h>
#include <Arduino.h>


class MidiOutputService {

public:
    MidiOutputService(HardwareSerial& midiSerial);

    void sendMessage(uint8_t* buf, uint8_t length);

private:
    HardwareSerial& _midiSerial;

};

#endif
