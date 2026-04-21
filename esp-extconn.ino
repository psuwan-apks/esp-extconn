#include "ConfigHandler.h"
#include "DigitalHandler.h"
#include "AnalogHandler.h"
#include "CommHandler.h"
#include "SensorHandler.h"
#include "SettingsHandler.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- ESP External World Connector ---");

  // Initialize EEPROM
  SettingsHandler::begin();

  // Load Internal Configuration
  if (!ConfigHandler::loadConfig()) {
    Serial.println("System Halt: Config load error");
    while(1);
  }

  JsonDocument& config = ConfigHandler::getConfig();

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

  Serial.println("Initialization Complete.");
}

void loop() {
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

  delay(2000);
}
