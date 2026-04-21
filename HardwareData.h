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
    {"pin": 35, "mode": "input", "name": "ADC sensor"},
    {"pin": 12, "mode": "output", "channel": 0, "freq": 5000, "res": 8, "name": "PWM Output"}
  ],
  "comm": {
    "i2c": {"sda": 32, "scl": 33, "freq": 100000},
    "spi": {"sck": 14, "miso": 12, "mosi": 15, "ss": 4},
    "uart": [
      {"port": 2, "baud": 115200, "rx": 5, "tx": 17, "dataBits": 8, "parity": 0, "stopBits": 1}
    ]
  },
  "sensors": {
    "touch": [15, 14],
    "hall": true
  }
}
)=====";

#endif
