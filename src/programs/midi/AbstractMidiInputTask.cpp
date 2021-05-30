#include "AbstractMidiInputTask.h"
#include "MidiConstants.h"


AbstractMidiInputTask::AbstractMidiInputTask(MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputService) :
    midiEventProcessor(midiEventProcessor),
    midiOutputService(midiOutputService) {

}

void AbstractMidiInputTask::handleMessage(uint8_t command, uint8_t channel, uint8_t data1, uint8_t data2) {
    Serial.println("");
    Serial.println("Command");
    Serial.println(command);
    Serial.println("Channel");
    Serial.println(channel);
    Serial.println("Data 1");
    Serial.println(data1);
    Serial.println("Data 2");
    Serial.println(data2);

    if(command == COMMAND_NOTEON) {
        midiEventProcessor.eventNoteOn(channel, data1, data2);
    } else if(command == COMMAND_NOTEOFF || (command == COMMAND_POLY_PRESSURE && data2 == 0)) {
        midiEventProcessor.eventNoteOff(channel, data1);
    } else if(command == COMMAND_POLY_PRESSURE) {
        midiEventProcessor.eventNotePressure(channel, data1, data2);
    } else if(command == COMMAND_CHAN_PRESSURE) {
        if(data1 <= 128) {
            midiEventProcessor.eventChannelPressure(channel, data1);
        }
    } else if(command == COMMAND_CONTROL_CHANGE) {
        // TODO handle LSB on same channel + 30
        handleControlChange(channel, data1, data2, 0);
    } else if(command == COMMAND_PITCH_BEND) {
        int16_t pitch = ((data2 * 128) + data1) - 8192;
        midiEventProcessor.eventPitchBend(channel, pitch);
    } else if(command == COMMAND_SYSTEM) {
        if(channel == SYSTEM_CLOCK) {
            midiEventProcessor.eventClock();
        } else if(channel == SYSTEM_START) {
            midiEventProcessor.eventStart();
        } else if(channel == SYSTEM_STOP) {
            midiEventProcessor.eventStop();
        } else if(channel == SYSTEM_RESET) {
            midiEventProcessor.eventReset();
        }
    }
}

void AbstractMidiInputTask::handleControlChange(uint8_t midiChannel, int8_t controlNumber, int8_t msbValue, int8_t lsbValue) {
    int16_t value = msbValue * 128 + lsbValue;
    midiEventProcessor.eventControlChange(midiChannel, controlNumber, value);
    prevCCChannel = -1;
    prevCCControl = -1;
    prevCCValue = -1;
}