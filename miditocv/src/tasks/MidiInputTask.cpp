#include "MidiInputTask.h"
#include "HardwareSerial.h"

#include <Arduino.h>


#define COMMAND_NOTEOFF 0x8
#define COMMAND_NOTEON 0x9
#define COMMAND_POLY_PRESSURE 0xA
#define COMMAND_CONTROL_CHANGE 0xB
#define COMMAND_PROGRAM_CHANGE 0xC
#define COMMAND_CHAN_PRESSURE 0xD
#define COMMAND_PITCH_BEND 0xE
#define COMMAND_SYSTEM 0xF

#define SYSTEM_CLOCK 0x8



#define HI_NYBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NYBBLE(b) ((b) & 0x0F)


MidiInputTask::MidiInputTask(MidiEventProcessor& midiEventProcessor) :
    _midiEventProcessor(midiEventProcessor) {
}

void MidiInputTask::init() {
    Task::init();
    Serial2.begin(31250);
}

void MidiInputTask::execute() {
    while(Serial2.available()) {
        byte byte1 = Serial2.read();
        if(byte1 >= 0x80) {

            byte command = HI_NYBBLE(byte1);
            byte channel = LO_NYBBLE(byte1);

            if(command != COMMAND_SYSTEM) {

                while(!Serial2.available()){}
                byte byte2 = Serial2.read();
                while(!Serial2.available()){}
                byte byte3 = Serial2.read();

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
                    // Serial.println("Note on ");
                    // Serial.println(byte2);
                    _midiEventProcessor.eventNoteOn(channel, byte2, byte3);
                }

                if(command == COMMAND_NOTEOFF || (command == COMMAND_POLY_PRESSURE && byte3 == 0)) {
                    _midiEventProcessor.eventNoteOff(channel, byte2);
                }

            } else { // command == COMMAND_SYSTEM

                // if(channel == SYSTEM_CLOCK) {
                //     //Serial.println("clock");
                // }
            }
        }
    }
}
