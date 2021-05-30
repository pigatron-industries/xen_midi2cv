#include "UsbMidiInputTask.h"
#include "MidiConstants.h"

UsbMidiInputTask::UsbMidiInputTask(MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputSevice) :
    AbstractMidiInputTask(midiEventProcessor, midiOutputService)  {
}

void UsbMidiInputTask::init() {
}

void UsbMidiInputTask::execute() {
    #ifdef USB_MIDI
    if(usbMIDI.read()) {
        byte command = HI_NYBBLE(usbMIDI.getType());
        byte channel = usbMIDI.getChannel() - 1;
        byte data1 = usbMIDI.getData1();
        byte data2 = usbMIDI.getData2();

        if(command == COMMAND_SYSTEM && channel == SYSTEM_EXCLUSIVE) {
            //handleSysex();
            return;
        }

        handleMessage(command, channel, data1, data2);
    }
    #endif
}