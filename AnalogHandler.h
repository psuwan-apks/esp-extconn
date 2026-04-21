#ifndef ANALOG_HANDLER_H
#define ANALOG_HANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class AnalogHandler {
public:
    static void setup(JsonArray pins);
    static int read(int pin);
    static void write(int pin, int value); // PWM or DAC
};

#endif
