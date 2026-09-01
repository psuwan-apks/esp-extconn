#include "ConfigHandler.h"
#include "DigitalHandler.h"
#include "AnalogHandler.h"
#include "CommHandler.h"
#include "SensorHandler.h"
#include "NetworkHandler.h"
#include "SettingsHandler.h"
#include "WebHandler.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  
  // Check for OTA mode trigger (Pin 4 held > 5 seconds)
  pinMode(4, INPUT_PULLUP);
  Serial.println("Checking OTA mode trigger (hold button for 5s)...");
  if (digitalRead(4) == LOW) {
    unsigned long start = millis();
    bool held = true;
    while (millis() - start < 5000) {
      if (digitalRead(4) == HIGH) {
        held = false;
        break;
      }
      if ((millis() - start) % 1000 == 0) {
        Serial.print(".");
      }
      delay(10);
    }
    if (held) {
      Serial.println("\nOTA Mode Activated!");
      NetworkHandler::forceOTA = true;
    } else {
      Serial.println("\nButton released, normal boot.");
    }
  }

  delay(500);
  Serial.println("\n--- ESP External World Connector ---");

  // Initialize EEPROM
  SettingsHandler::begin();

  // Load Internal Configuration
  if (!ConfigHandler::loadConfig()) {
    Serial.println("System Halt: Config load error");
    while(1);
  }

  JsonDocument& config = ConfigHandler::getConfig();

  // Setup Network Components
  NetworkHandler::setup();

  // Setup Digital IO
  if (config.containsKey("digital")) {
    DigitalHandler::setup(config["digital"]);
  }

  // Setup Analog IO
  if (config.containsKey("analog")) {
    AnalogHandler::setup(config["analog"]);
  }

  // Setup Communication (I2C, SPI, UART)
  if (config.containsKey("comm")) {
    CommHandler::setup(config["comm"]);
    CommHandler::i2cScan(); // Optional: Scan I2C on startup
  }

  // Setup Sensors
  if (config.containsKey("sensors")) {
     SensorHandler::setup(config["sensors"]);
  }

  WebHandler::setup();

  Serial.println("Initialization Complete.");
}

void loop() {
  NetworkHandler::loop();  // Process DNS for captive portal in AP mode
  WebHandler::loop();      // Handle HTTP clients
  // Example: Read a digital pin every second
  // bool btnState = DigitalHandler::read(4);
  // Serial.print("Button 4: "); Serial.println(btnState);

  // Example: Read Analog
  // int val = AnalogHandler::read(35);
  // Serial.print("Analog 35: "); Serial.println(val);

  // Example: Read Touch
  // int touchVal = SensorHandler::readTouch(15);
  // Serial.print("Touch 15: "); Serial.println(touchVal);
  
  // Example: Read Hall
  // int hallVal = SensorHandler::readHall();
  // Serial.print("Hall: "); Serial.println(hallVal);

  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000) {
      lastUpdate = millis();
      // Example: Read Analog
      // int val = AnalogHandler::read(35);
      // Serial.print("Analog 35: "); Serial.println(val);
  }
}
