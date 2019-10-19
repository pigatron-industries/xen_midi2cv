#include "MidiEventProcessor.h"

#define MIDI_CHANNELS 16

MidiEventProcessor::MidiEventProcessor(Configuration& config, StatusLedTask& statusLedTask, GateOutput& gateOutput, PitchCvOutput& pitchCvOutput) :
        _config(config),
        _statusLedTask(statusLedTask),
        _gateOutput(gateOutput),
        _pitchCvOutput(pitchCvOutput) {
    _channelMapping = new uint8_t[MIDI_CHANNELS];
    _lastNoteChannel = new uint8_t[_pitchCvOutput.getSize()];

    // get channel mappings from config
    for(uint8_t i = 0; i < MIDI_CHANNELS; i++) {
        _channelMapping[i] = _config.getCvChannelMapping(i).from;
    }
}

void MidiEventProcessor::eventNoteOn(uint8_t midiChannel, uint8_t note, uint8_t velocity) {
    //Serial.println("MidiEventProcessor::eventNoteOn:start");

    uint8_t cvChannel = getCvOutputChannel(midiChannel);
    if(cvChannel == -1) {
        //Serial.println("MidiEventProcessor::eventNoteOn:end -1");
        return;
    }

    // Save note channel
    _lastNoteChannel[cvChannel] = note;

    // convert note number to Pitch CV Output

    // convert velocity to Cv Output

    // send trigger and gate output
    _gateOutput.setValue(cvChannel, HIGH);
    _gateOutput.sendData();

    _statusLedTask.blinkGreen();
    //Serial.println("MidiEventProcessor::eventNoteOn:end");
}

void MidiEventProcessor::eventNoteOff(uint8_t midiChannel, uint8_t note) {
    //Serial.println("MidiEventProcessor::eventNoteOff:start");

    uint8_t cvChannel = getCvOutputChannel(midiChannel, note);
    if(cvChannel == -1) {
        //Serial.println("MidiEventProcessor::eventNoteOff:end -1");
        return;
    }

    // Clear note channel
    _lastNoteChannel[cvChannel] = -1;

    // convert midi channel and note to Pitch Cv Channel

    // stop gate output
    _gateOutput.setValue(cvChannel, LOW);
    _gateOutput.sendData();

    _statusLedTask.blinkRed();
    //Serial.println("MidiEventProcessor::eventNoteOff:end");
}


uint8_t MidiEventProcessor::getCvOutputChannel(uint8_t midiChannel) {
    //Serial.println("MidiEventProcessor::getCvOutputChannel(midiChannel):start");
    uint8_t currentCvChannel = _channelMapping[midiChannel];
    ChannelMapping channelConfig = _config.getCvChannelMapping(midiChannel); //TODO handle no channel mapping

    if(channelConfig.from < channelConfig.to) {
        if(currentCvChannel == channelConfig.to) {
            _channelMapping[midiChannel] = channelConfig.from;
        } else {
            _channelMapping[midiChannel]++;
        }
    }

    //Serial.println("MidiEventProcessor::getCvOutputChannel:end");
    return currentCvChannel;
}

uint8_t MidiEventProcessor::getCvOutputChannel(uint8_t midiChannel, uint8_t note) {
    //Serial.println("MidiEventProcessor::getCvOutputChannel(midiChannel, note):start");
    for(uint8_t i = 0; i < _pitchCvOutput.getSize(); i++) {
        if(_lastNoteChannel[i] == note) {
            //Serial.println("MidiEventProcessor::getCvOutputChannel(midiChannel, note):end");
            return i;
        }
    }

    //Serial.println("MidiEventProcessor::getCvOutputChannel(midiChannel, note):end -1");
    return -1;
}
