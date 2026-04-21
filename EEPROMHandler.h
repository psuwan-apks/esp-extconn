#ifndef EEPROM_HANDLER_H
#define EEPROM_HANDLER_H

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMHandler {
public:
    static void begin(size_t size);
    
    template <typename T>
    static void write(int address, const T& data) {
        EEPROM.put(address, data);
        EEPROM.commit();
    }
    
    template <typename T>
    static void read(int address, T& data) {
        EEPROM.get(address, data);
    }
};

#endif
