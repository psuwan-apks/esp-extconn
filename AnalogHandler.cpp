#include "AnalogHandler.h"

void AnalogHandler::setup(JsonArray pins) {
    for (JsonObject pinObj : pins) {
        int pin = pinObj["pin"];
        const char* mode = pinObj["mode"];

        if (strcmp(mode, "input") == 0) {
            // Analog inputs don't strictly need pinMode in many cases, but for clarity:
            pinMode(pin, INPUT);
        } else if (strcmp(mode, "output") == 0) {
            // PWM Setup
#if defined(ESP32)
            int channel = pinObj["channel"] | 0;
            int freq = pinObj["freq"] | 5000;
            int res = pinObj["res"] | 8;
            ledcSetup(channel, freq, res);
            ledcAttachPin(pin, channel);
#else
            pinMode(pin, OUTPUT);
#endif
        }
    }
}

int AnalogHandler::read(int pin) {
    return analogRead(pin);
}

void AnalogHandler::write(int pin, int value) {
#if defined(ESP32)
    // Dynamic lookup of channel would be better, but simplified for now:
    // If it's a DAC pin (25, 26)
    if (pin == 25 || pin == 26) {
        dacWrite(pin, value);
    } else {
        // This requires tracking which pin is on which channel.
        // For simplicity, let's assume value passed is for ledcWrite if configured.
        // In a real app, you'd map pin -> channel.
    }
#else
    analogWrite(pin, value);
#endif
}
