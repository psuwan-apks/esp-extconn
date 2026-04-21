#include "SettingsHandler.h"

void SettingsHandler::begin() {
    EEPROMHandler::begin(EEPROM_SIZE);
}

bool SettingsHandler::loadUartSettings(int portIndex, UartSettings& settings) {
    int address = portIndex * sizeof(UartSettings);
    EEPROMHandler::read(address, settings);
    
    return (settings.magic == EEPROM_MAGIC);
}

void SettingsHandler::saveUartSettings(int portIndex, const UartSettings& settings) {
    int address = portIndex * sizeof(UartSettings);
    UartSettings s = settings;
    s.magic = EEPROM_MAGIC;
    EEPROMHandler::write(address, s);
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
