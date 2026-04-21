#ifndef SETTINGS_HANDLER_H
#define SETTINGS_HANDLER_H

#include <Arduino.h>
#include "EEPROMHandler.h"

#define EEPROM_SIZE 1024
#define EEPROM_MAGIC 0xFEEDBEEF

struct UartSettings {
    uint32_t baudrate;
    uint8_t port;
    uint8_t dataBits; // 5, 6, 7, 8
    uint8_t parity;   // 0: None, 1: Odd, 2: Even
    uint8_t stopBits; // 1, 2
};

struct AppSettings {
    uint32_t magic;
    char company[32];
    char firmwareStr[16];
    char web_pass[32];
    
    // WiFi
    uint8_t wifi_mode; // 0: STA, 1: AP
    char wifi_ssid[32];
    char wifi_pass[64];
    
    // Ethernet
    uint8_t eth_dhcp; // 1: DHCP, 0: Static IP
    char eth_ip[16];
    char eth_gw[16];
    char eth_mask[16];
    
    // Uart
    UartSettings uart;
};

class SettingsHandler {
public:
    static AppSettings settings;

    static void begin();
    static void loadSettings();
    static void saveSettings();
    static void resetToDefault();
    
    // Maps standard JSON strings to serial config flags
    static uint32_t getSerialConfig(uint8_t db, uint8_t pr, uint8_t sb);
};

#endif
