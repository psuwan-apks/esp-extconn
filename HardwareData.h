#ifndef HARDWARE_DATA_H
#define HARDWARE_DATA_H

#include <Arduino.h>

// This file defines the hardware configuration as a JSON string to avoid 
// the need for external filesystem (SPIFFS/LittleFS) uploads.
const char* const HARDWARE_CONFIG = R"=====(
{
  "digital": [
    {"pin": 2, "mode": "output", "name": "Built-in LED"},
    {"pin": 4, "mode": "input_pullup", "name": "Button 1"}
  ],
  "analog": [
    {"pin": 34, "mode": "input", "name": "LDR sensor"},
    {"pin": 25, "mode": "output", "channel": 0, "freq": 5000, "res": 8, "name": "PWM Output"}
  ],
  "comm": {
    "i2c": {"sda": 21, "scl": 22, "freq": 100000},
    "spi": {"sck": 18, "miso": 19, "mosi": 23, "ss": 5},
    "uart": [
      {"port": 2, "baud": 115200, "rx": 16, "tx": 17, "dataBits": 8, "parity": 0, "stopBits": 1}
    ]
  },
  "sensors": {
    "touch": [15, 13],
    "hall": true
  }
}
)=====";

#endif
