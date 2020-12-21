#include "MidiOutputService.h"
#include "HardwareSerial.h"
#include "../../hwconfig.h"

MidiOutputService::MidiOutputService(HardwareSerial& _midiSerial1, HardwareSerial& _midiSerial2) :
    midiSerial1(_midiSerial1),
    midiSerial2(_midiSerial2) {
        _midiSerial1.begin(MIDI_BAUD);
        _midiSerial2.begin(MIDI_BAUD);
}

void MidiOutputService::sendMessage(uint8_t* buf, uint8_t length) {
    midiSerial1.write(buf, length);
    midiSerial2.write(buf, length);
}

void MidiOutputService::sendByte(uint8_t byte) {
    Serial.println("MidiOutputService::sendByte");
    midiSerial1.write(byte);
    midiSerial2.write(byte);
}
