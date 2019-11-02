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


MidiInputTask::MidiInputTask(MidiEventProcessor& midiEventProcessor) :
    _midiEventProcessor(midiEventProcessor) {
}

void MidiInputTask::init() {
    Task::init();
    Serial2.begin(MIDI_BAUD);
}

byte MidiInputTask::getByte() {
    while(!Serial2.available()){}
    return Serial2.read();
}

void MidiInputTask::execute() {
    while(Serial2.available()) {
        byte byte1 = getByte();
        if(byte1 >= 0x80) {

            byte command = HI_NYBBLE(byte1);
            byte channel = LO_NYBBLE(byte1);

            if(command != COMMAND_SYSTEM) {
                byte byte2 = getByte();
                byte byte3 = getByte();

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
                }

                if(command == COMMAND_NOTEOFF || (command == COMMAND_POLY_PRESSURE && byte3 == 0)) {
                    _midiEventProcessor.eventNoteOff(channel, byte2);
                }

                if(command == COMMAND_POLY_PRESSURE) {
                    _midiEventProcessor.eventNotePressure(channel, byte2, byte3);
                }

                if(command == COMMAND_CONTROL_CHANGE) {
                    _midiEventProcessor.eventControlChange(channel, byte2, byte3);
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

void MidiInputTask::handleSysex() {
    memset(sysexBuffer, 0, SYSEX_BUFFER_SIZE);
    size_t size = Serial2.readBytesUntil(SYSTEM_EXCLUSIVE_END, sysexBuffer, SYSEX_BUFFER_SIZE);

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
