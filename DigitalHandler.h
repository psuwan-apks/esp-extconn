#ifndef DIGITAL_HANDLER_H
#define DIGITAL_HANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DigitalHandler {
public:
    static void setup(JsonArray pins);
    static void update();
    static void write(int pin, bool value);
    static bool read(int pin);
};

#endif
