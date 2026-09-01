#include "SensorHandler.h"

void SensorHandler::setup(JsonObject sensors) {
    Serial.println("Sensors Initialized");
}

int SensorHandler::readTouch(int pin) {
    // touchRead() is still available in ESP32 core v3.x on original ESP32
#if defined(CONFIG_IDF_TARGET_ESP32)
    return touchRead(pin);
#else
    return -1; // Not supported on newer ESP32 chips (S2/S3/C3/H2)
#endif
}

int SensorHandler::readHall() {
    // hallRead() was REMOVED in ESP32 Arduino core v3.x entirely
    return -1;
}
