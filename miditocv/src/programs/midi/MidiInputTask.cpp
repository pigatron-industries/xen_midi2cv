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


MidiInputTask::MidiInputTask(HardwareSerial& midiSerial, MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputService) :
    _midiSerial(midiSerial),
    _midiEventProcessor(midiEventProcessor),
    _midiOutputService(midiOutputService) {
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

        uint8_t messageBuffer[MESSAGE_BUFFER_SIZE];
        messageBuffer[0] = getByte();

        if(messageBuffer[0] >= 0x80) { // start of midi message
            uint8_t length = 0;

            byte command = HI_NYBBLE(messageBuffer[0]);
            byte channel = LO_NYBBLE(messageBuffer[0]);

            if(command != COMMAND_SYSTEM) {

                messageBuffer[1] = getByte();
                if(command != COMMAND_CHAN_PRESSURE && command != COMMAND_PROGRAM_CHANGE) {
                    messageBuffer[2] = getByte();
                    length = 3;
                } else {
                    messageBuffer[2] = 0;
                    length = 2;
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
                    _midiEventProcessor.eventNoteOn(channel, messageBuffer[1], messageBuffer[2]);
                } else if(command == COMMAND_NOTEOFF || (command == COMMAND_POLY_PRESSURE && messageBuffer[2] == 0)) {
                    _midiEventProcessor.eventNoteOff(channel, messageBuffer[1]);
                } else if(command == COMMAND_POLY_PRESSURE) {
                    _midiEventProcessor.eventNotePressure(channel, messageBuffer[1], messageBuffer[2]);
                } else if(command == COMMAND_CHAN_PRESSURE) {
                      if(messageBuffer[1] <= 128) {
                          _midiEventProcessor.eventChannelPressure(channel, messageBuffer[1]);
                      }
                } else if(command == COMMAND_CONTROL_CHANGE) {
                      handleControlChange(channel, messageBuffer[1], messageBuffer[2], 0);
                } else if(command == COMMAND_PITCH_BEND) {
                    int16_t pitch = ((messageBuffer[2] * 128) + messageBuffer[1]) - 8192;
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
