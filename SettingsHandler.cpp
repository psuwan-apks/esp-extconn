#include "SettingsHandler.h"
#include <string.h>

AppSettings SettingsHandler::settings;

void SettingsHandler::begin() {
    EEPROMHandler::begin(EEPROM_SIZE);
    loadSettings();
}

void SettingsHandler::loadSettings() {
    EEPROMHandler::read(0, settings);
    
    if (settings.magic != EEPROM_MAGIC) {
        Serial.println("EEPROM not initialized, applying defaults.");
        resetToDefault();
    } else {
        Serial.println("Settings loaded from EEPROM");
    }
}

void SettingsHandler::saveSettings() {
    settings.magic = EEPROM_MAGIC;
    EEPROMHandler::write(0, settings);
    Serial.println("Settings saved to EEPROM");
}

void SettingsHandler::resetToDefault() {
    memset(&settings, 0, sizeof(AppSettings));
    
    settings.magic = EEPROM_MAGIC;
    strncpy(settings.company, "My Company", sizeof(settings.company) - 1);
    strncpy(settings.firmwareStr, "1.0.0", sizeof(settings.firmwareStr) - 1);
    strncpy(settings.web_pass, "admin1234", sizeof(settings.web_pass) - 1);
    
    settings.wifi_mode = 0; // STA
    strncpy(settings.wifi_ssid, "MyRouter", sizeof(settings.wifi_ssid) - 1);
    strncpy(settings.wifi_pass, "Password123", sizeof(settings.wifi_pass) - 1);
    
    settings.eth_dhcp = 1;
    strncpy(settings.eth_ip, "192.168.1.100", sizeof(settings.eth_ip) - 1);
    strncpy(settings.eth_gw, "192.168.1.1", sizeof(settings.eth_gw) - 1);
    strncpy(settings.eth_mask, "255.255.255.0", sizeof(settings.eth_mask) - 1);

    settings.uart.baudrate = 115200;
    settings.uart.port = 2;
    settings.uart.dataBits = 8;
    settings.uart.parity = 0;
    settings.uart.stopBits = 1;
    
    saveSettings();
}

uint32_t SettingsHandler::getSerialConfig(uint8_t db, uint8_t pr, uint8_t sb) {
    // Mapping for ESP32 serial configs
    if (db == 7) {
        if (pr == 2) return (sb == 1) ? SERIAL_7E1 : SERIAL_7E2;
        if (pr == 1) return (sb == 1) ? SERIAL_7O1 : SERIAL_7O2;
        return (sb == 1) ? SERIAL_7N1 : SERIAL_7N2;
    }
    
    if (db == 8) {
        if (pr == 2) return (sb == 1) ? SERIAL_8E1 : SERIAL_8E2;
        if (pr == 1) return (sb == 1) ? SERIAL_8O1 : SERIAL_8O2;
        return (sb == 1) ? SERIAL_8N1 : SERIAL_8N2;
    }
    
    return SERIAL_8N1;
}
