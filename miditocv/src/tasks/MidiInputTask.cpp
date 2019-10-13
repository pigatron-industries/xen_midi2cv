#include "MidiInputTask.h"
#include "HardwareSerial.h"

#include <Arduino.h>


#define COMMAND_NOTEOFF 8
#define COMMAND_NOTEON 9



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
        byte byte2 = Serial2.read();
        byte byte3 = Serial2.read();
        byte command = HI_NYBBLE(byte1);
        byte channel = LO_NYBBLE(byte1);

        Serial.println("");
        Serial.println("Command");
        Serial.println(command);
        Serial.println("Channel");
        Serial.println(channel);
        Serial.println("Data 1");
        Serial.println(byte2);
        Serial.println("Data 2");
        Serial.println(byte3);

        if(command == COMMAND_NOTEON) {
            _midiEventProcessor.eventNoteOn(channel, byte2, byte3);
        }

        if(command == COMMAND_NOTEOFF) {
            _midiEventProcessor.eventNoteOff(channel, byte2);
        }
    }
}
