#ifndef UsbMidiInputTask_h
#define UsbMidiInputTask_h

#include <inttypes.h>

#include "AbstractMidiInputTask.h"
#include "MidiEventProcessor.h"
#include "MidiOutputService.h"
#include "usb_names.h"

#define SYSEX_BUFFER_SIZE 100
#define MESSAGE_BUFFER_SIZE 3

class UsbMidiInputTask : public AbstractMidiInputTask {

public:
    UsbMidiInputTask(MidiEventProcessor& midiEventProcessor, MidiOutputService& midiOutputSevice);
    void init();
    void execute();

};

#endif
