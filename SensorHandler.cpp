#include "SensorHandler.h"

void SensorHandler::setup(JsonObject sensors) {
    // Touch pins configuration can be handled here if specific thresholds are needed
    Serial.println("Sensors Initialized");
}

int SensorHandler::readTouch(int pin) {
#if defined(ESP32) && !defined(CONFIG_IDF_TARGET_ESP32C3) && !defined(CONFIG_IDF_TARGET_ESP32H2)
    return touchRead(pin);
#else
    return -1; // Not supported
#endif
}

int SensorHandler::readHall() {
#if defined(ESP32) && !defined(CONFIG_IDF_TARGET_ESP32S2) && !defined(CONFIG_IDF_TARGET_ESP32S3) && !defined(CONFIG_IDF_TARGET_ESP32C3)
    return hallRead();
#else
    return -1; // Not supported on newer ESP32 chips or ESP8266
#endif
}
