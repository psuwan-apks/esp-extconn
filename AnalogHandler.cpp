#include "AnalogHandler.h"

void AnalogHandler::setup(JsonArray pins) {
    for (JsonObject pinObj : pins) {
        int pin = pinObj["pin"];
        const char* mode = pinObj["mode"];

        if (strcmp(mode, "input") == 0) {
            pinMode(pin, INPUT);
        } else if (strcmp(mode, "output") == 0) {
            // ESP32 Arduino core v3.x: ledcSetup/ledcAttachPin removed.
            // New API: ledcAttach(pin, freq, resolution)
            int freq = pinObj["freq"] | 5000;
            int res  = pinObj["res"]  | 8;
            ledcAttach(pin, freq, res);
        }
    }
}

int AnalogHandler::read(int pin) {
    return analogRead(pin);
}

void AnalogHandler::write(int pin, int value) {
    // ESP32 core v3.x: use ledcWrite(pin, duty) directly (no channel needed)
    ledcWrite(pin, value);
}
