#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class SensorHandler {
public:
    static void setup(JsonObject sensors);
    static int readTouch(int pin);
    static int readHall();
};

#endif
