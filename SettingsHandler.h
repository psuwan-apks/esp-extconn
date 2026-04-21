#ifndef SETTINGS_HANDLER_H
#define SETTINGS_HANDLER_H

#include <Arduino.h>
#include "EEPROMHandler.h"

#define EEPROM_SIZE 512
#define EEPROM_MAGIC 0xABCD1234

struct UartSettings {
    uint32_t magic;
    uint32_t baudrate;
    uint8_t port;
    uint8_t dataBits; // 5, 6, 7, 8
    uint8_t parity;   // 0: None, 1: Odd, 2: Even
    uint8_t stopBits; // 1, 2
};

class SettingsHandler {
public:
    static void begin();
    static bool loadUartSettings(int portIndex, UartSettings& settings);
    static void saveUartSettings(int portIndex, const UartSettings& settings);
    
    // Maps standard JSON strings to serial config flags
    static uint32_t getSerialConfig(uint8_t db, uint8_t pr, uint8_t sb);
};

#endif
