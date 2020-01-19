#include "MidiOutputService.h"
#include "HardwareSerial.h"


MidiOutputService::MidiOutputService(HardwareSerial& midiSerial) :
    _midiSerial(midiSerial) {
}

void MidiOutputService::sendMessage(uint8_t* buf, uint8_t length) {
    _midiSerial.write(buf, length);
}
