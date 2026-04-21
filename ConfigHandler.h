#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "HardwareData.h"

class ConfigHandler {
public:
    static bool loadConfig() {
        DeserializationError error = deserializeJson(doc, HARDWARE_CONFIG);
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.f_str());
            return false;
        }
        return true;
    }
    
    static JsonDocument& getConfig() {
        return doc;
    }

private:
    static StaticJsonDocument<4096> doc;
};

#endif
