#include "EEPROMHandler.h"

void EEPROMHandler::begin(size_t size) {
    EEPROM.begin(size);
    Serial.print("EEPROM Initialized with size: "); Serial.println(size);
}
