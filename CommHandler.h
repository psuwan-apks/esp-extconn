#ifndef COMM_HANDLER_H
#define COMM_HANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>

class CommHandler {
public:
    static void setup(JsonObject comms);
    static void i2cScan();
    static void uartSend(int port, const char* data);
};

#endif
