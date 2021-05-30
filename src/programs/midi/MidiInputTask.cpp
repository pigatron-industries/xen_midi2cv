#include "MidiInputTask.h"
#include "HardwareSerial.h"
#include "MidiConstants.h"

#include "../../lib/base64/Base64.h"
#include "../../hwconfig.h"

#include <Arduino.h>


MidiInputTask::MidiInputTask(HardwareSerial& midiSerial, MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputService) :
    AbstractMidiInputTask(midiEventProcessor, midiOutputService),
    _midiSerial(midiSerial) {
}

void MidiInputTask::init() {
    _midiSerial.begin(MIDI_BAUD);
}

byte MidiInputTask::getByte() {
    while(!_midiSerial.available()){}
    uint8_t byte = _midiSerial.read();
    passThrough(byte);
    return byte;
}

void MidiInputTask::passThrough(byte byte) {
    Serial2.write(byte);
    if(&_midiSerial != &Serial3) {
        Serial3.write(byte);
    }
}

void MidiInputTask::execute() {
    while(_midiSerial.available()) {
        byte readByte = getByte();

        if(readByte >= 0x80) { // start of midi message
            byte command = HI_NYBBLE(readByte);
            byte channel = LO_NYBBLE(readByte);
            byte data1 = 0;
            byte data2 = 0;

            if(command != COMMAND_SYSTEM) {
                data1 = getByte();
                if(command != COMMAND_CHAN_PRESSURE && command != COMMAND_PROGRAM_CHANGE) {
                    data2 = getByte();
                }
            } else { // command == COMMAND_SYSTEM
                if(channel == SYSTEM_EXCLUSIVE) {
                    handleSysex();
                    return;
                } 
            }

            handleMessage(command, channel, data1, data2);
        }
    }
}

void MidiInputTask::handleSysex() {
    memset(sysexBuffer, 0, SYSEX_BUFFER_SIZE);
    size_t size = _midiSerial.readBytesUntil(SYSTEM_EXCLUSIVE_END, sysexBuffer, SYSEX_BUFFER_SIZE);

    Serial.println("System config message recieved:");
    Serial.print("     ");
    for(unsigned int i = 0; i < size; i++) {
        Serial.print((char)sysexBuffer[i]);
    }
    Serial.println();
    Serial.println();

    int decodedSize = base64_decode((char*)sysexBufferDecoded, (char*)sysexBuffer, size);
    midiEventProcessor.eventSystemConfig(sysexBufferDecoded, decodedSize);
}
