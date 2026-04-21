#include "DigitalHandler.h"

void DigitalHandler::setup(JsonArray pins) {
    for (JsonObject pinObj : pins) {
        int pin = pinObj["pin"];
        const char* mode = pinObj["mode"];
        
        if (strcmp(mode, "output") == 0) {
            pinMode(pin, OUTPUT);
        } else if (strcmp(mode, "input") == 0) {
            pinMode(pin, INPUT);
        } else if (strcmp(mode, "input_pullup") == 0) {
            pinMode(pin, INPUT_PULLUP);
        }
    }
}

void DigitalHandler::update() {
    // Logic for periodic digital tasks if any
}

void DigitalHandler::write(int pin, bool value) {
    digitalWrite(pin, value);
}

bool DigitalHandler::read(int pin) {
    return digitalRead(pin);
}
