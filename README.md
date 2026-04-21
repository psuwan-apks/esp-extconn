# ESP External World Connector

A modular, configuration-driven Arduino project for ESP32 and ESP8266. This project allows you to interface with various electronic components (sensors, actuators, communication modules) simply by editing a JSON configuration file, without needing to rewrite code for different pinouts.

## Features

- **Hardware Agnostic**: Supports both ESP32 and ESP8266.
- **Config Driven**: All pin assignments and protocols (I2C, SPI, UART) are defined in `config.json`.
- **Digital I/O**: Supports output and input (with internal pullups).
- **Analog I/O**: Supports analog input and PWM output (including ESP32's `ledc` and DAC).
- **Communication Protocols**: 
  - **I2C**: Configurable SDA/SCL pins and frequency + Automatic I2C scanner at boot.
  - **SPI**: Configurable SCK, MISO, MOSI, and SS pins.
  - **UART**: Supports multiple hardware serial ports (e.g., Serial1, Serial2 on ESP32).
- **Specialized Sensors**: Built-in support for ESP32 Touch and Hall Effect sensors.

## Prerequisites

### Libraries
You must install the following library via the Arduino Library Manager:
- **ArduinoJson** (v6 or v7)

### Hardware Support
Install the board packages for your device:
- **ESP32** by Espressif Systems
- **ESP8266** by ESP8266 Community

## Project Structure

- `esp-extconn.ino`: Main project entry point.
- `ConfigHandler`: Manages the parsing of the internal JSON configuration.
- `DigitalHandler`: Logic for digital pins.
- `AnalogHandler`: Logic for analog and PWM pins.
- `CommHandler`: Logic for I2C, SPI, and UART.
- `SensorHandler`: Logic for ESP32-specific sensors.
- `SettingsHandler` & `EEPROMHandler`: Manages saving and loading dynamic settings (like UART config) to EEPROM.
- `HardwareData.h`: The hardware configuration file defined as a JSON string.

## Setup Instructions

### 1. Configure Hardware
Edit the `HardwareData.h` file in the project folder. Change the `HARDWARE_CONFIG` string to match your wiring.
Example for ESP32:
```json
const char* HARDWARE_CONFIG = R"=====(
{
  "digital": [
    {"pin": 2, "mode": "output", "name": "Built-in LED"},
    {"pin": 4, "mode": "input_pullup", "name": "Button 1"}
  ],
  "analog": [
    {"pin": 34, "mode": "input", "name": "LDR sensor"},
    {"pin": 25, "mode": "output", "channel": 0, "freq": 5000, "res": 8, "name": "PWM Output"}
  ],
  "comm": {
    "i2c": {"sda": 21, "scl": 22, "freq": 100000},
    "spi": {"sck": 18, "miso": 19, "mosi": 23, "ss": 5},
    "uart": [
      {"port": 2, "baud": 115200, "rx": 16, "tx": 17, "dataBits": 8, "parity": 0, "stopBits": 1}
    ]
  },
  "sensors": {
    "touch": [15, 13],
    "hall": true
  }
}
)=====";
```

### 2. Upload Code
1. Open `esp-extconn.ino` in the Arduino IDE.
2. Select your board (ESP32 Dev Module, Generic ESP8266, etc.).
3. Click **Upload**.

(Note: You no longer need to upload external files to the device filesystem).

## Usage
Once booted, the ESP will:
1. Initialize the Serial monitor at **115200 baud**.
2. Initialize EEPROM and related settings.
3. Load the internal `HARDWARE_CONFIG` from memory.
4. Configure all defined pins and peripherals based on the JSON configuration.
5. If I2C is enabled, it will print a list of detected addresses to the console.

## Customization
To add custom logic for your specific sensors, you can modify the `loop()` function in `esp-extconn.ino` to read from the handlers using the simplified methods:
- `DigitalHandler::read(pin)`
- `AnalogHandler::read(pin)`
- `SensorHandler::readTouch(pin)`
