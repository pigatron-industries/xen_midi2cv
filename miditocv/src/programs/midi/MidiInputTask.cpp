#include "MidiInputTask.h"
#include "HardwareSerial.h"

#include "src/lib/base64/Base64.h"
#include "src/hwconfig.h"

#include <Arduino.h>


#define COMMAND_NOTEOFF 0x8
#define COMMAND_NOTEON 0x9
#define COMMAND_POLY_PRESSURE 0xA
#define COMMAND_CONTROL_CHANGE 0xB
#define COMMAND_PROGRAM_CHANGE 0xC
#define COMMAND_CHAN_PRESSURE 0xD
#define COMMAND_PITCH_BEND 0xE
#define COMMAND_SYSTEM 0xF

#define SYSTEM_EXCLUSIVE 0x0
#define SYSTEM_CLOCK 0x8

#define SYSTEM_EXCLUSIVE_ID 0x7D
#define SYSTEM_EXCLUSIVE_END 0xF7




#define HI_NYBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NYBBLE(b) ((b) & 0x0F)


MidiInputTask::MidiInputTask(HardwareSerial& midiSerial, MidiEventProcessor& midiEventProcessor) :
    _midiSerial(midiSerial),
    _midiEventProcessor(midiEventProcessor) {
}

void MidiInputTask::init() {
    Task::init();
    _midiSerial.begin(MIDI_BAUD);
}

byte MidiInputTask::getByte() {
    while(!_midiSerial.available()){}
    return _midiSerial.read();
}

void MidiInputTask::execute() {
    while(_midiSerial.available()) {
        byte byte1 = getByte();
        if(byte1 >= 0x80) {

            byte command = HI_NYBBLE(byte1);
            byte channel = LO_NYBBLE(byte1);

            if(command != COMMAND_SYSTEM) {
                byte byte2 = getByte();
                byte byte3 = 0;
                if(command != COMMAND_CHAN_PRESSURE && command != COMMAND_PROGRAM_CHANGE) {
                    byte3 = getByte();
                }

                // Serial.println("");
                // Serial.println("Command");
                // Serial.println(command);
                // Serial.println("Channel");
                // Serial.println(channel);
                // Serial.println("Data 1");
                // Serial.println(byte2);
                // Serial.println("Data 2");
                // Serial.println(byte3);

                if(command == COMMAND_NOTEON) {
                    _midiEventProcessor.eventNoteOn(channel, byte2, byte3);
                } else if(command == COMMAND_NOTEOFF || (command == COMMAND_POLY_PRESSURE && byte3 == 0)) {
                    _midiEventProcessor.eventNoteOff(channel, byte2);
                } else if(command == COMMAND_POLY_PRESSURE) {
                    _midiEventProcessor.eventNotePressure(channel, byte2, byte3);
                } else if(command == COMMAND_CHAN_PRESSURE) {
                      if(byte2 <= 128) {
                          _midiEventProcessor.eventChannelPressure(channel, byte2);
                      }
                } else if(command == COMMAND_CONTROL_CHANGE) {
                      handleControlChange(channel, byte2, byte3, 0);
                } else if(command == COMMAND_PITCH_BEND) {
                    int16_t pitch = ((byte3 * 128) + byte2) - 8192;
                    _midiEventProcessor.eventPitchBend(channel, pitch);
                }

            } else { // command == COMMAND_SYSTEM

                if(channel == SYSTEM_CLOCK) {
                    //Serial.println("clock");
                }
                else if(channel == SYSTEM_EXCLUSIVE) {
                    handleSysex();
                }
            }
        }
    }
}

void MidiInputTask::handleControlChange(uint8_t midiChannel, int8_t controlNumber, int8_t msbValue, int8_t lsbValue) {
    int16_t value = msbValue * 128 + lsbValue;
    _midiEventProcessor.eventControlChange(midiChannel, controlNumber, value);
    prevCCChannel = -1;
    prevCCControl = -1;
    prevCCValue = -1;
}

void MidiInputTask::handleSysex() {
    memset(sysexBuffer, 0, SYSEX_BUFFER_SIZE);
    size_t size = _midiSerial.readBytesUntil(SYSTEM_EXCLUSIVE_END, sysexBuffer, SYSEX_BUFFER_SIZE);

    Serial.println("System config message recieved:");
    Serial.print("     ");
    for(int i = 0; i < size; i++) {
        Serial.print((char)sysexBuffer[i]);
    }
    Serial.println();
    Serial.println();

    int decodedSize = base64_decode((char*)sysexBufferDecoded, (char*)sysexBuffer, size);
    _midiEventProcessor.eventSystemConfig(sysexBufferDecoded, decodedSize);
}
