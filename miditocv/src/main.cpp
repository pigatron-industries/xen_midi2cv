#include <Arduino.h>

#include "src/drivers/StatusLed.h"
#include "src/tasks/StatusLedTask.h"
#include "src/tasks/MidiInputTask.h"
#include "src/lib/TaskManager.h"


// Hardware setup

// Status LEDs
StatusLed statusLed = StatusLed(LED_RED, LED_BLUE, LED_GREEN);

// USART2 For receiving MIDI - USART_B_RX - STM32 pin: PD6 - Pin 4 - Pin name D52
//HardwareSerial Serial2(PD5, PD6);




StatusLedTask statusLedTask = StatusLedTask(statusLed);
MidiInputTask midiInputTask = MidiInputTask(statusLedTask);


void bootstrap() {
    Serial.begin(115200);

    Task* tasks[] = { &statusLedTask, &midiInputTask };
    TaskManager taskManager(tasks, 2);
    taskManager.run();
}
