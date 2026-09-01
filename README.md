# ESP External World Connector

A modular, configuration-driven Arduino project for ESP32 (specifically configured for the WT32-ETH01 board). This project allows you to interface with various electronic components (sensors, actuators, communication modules) simply by editing a JSON configuration file, without needing to rewrite code for different pinouts.

## Features

- **Hardware Agnostic**: Supports ESP32.
- **Network Support**: Configurable Ethernet (WT32-ETH01 LAN8720) and WiFi (STA/AP).
- **Web Configuration Portal**: Built-in plain HTML web server hosted on port 80. Includes an automatic Captive Portal when in AP mode and password-protection for configuration settings. Default password is `admin1234`.
- **EEPROM Storage**: Web configuration and passwords are persistently saved in EEPROM so configuration is loaded consistently across boot sequences.
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

## Pin Mapping — WT32-ETH01

```
                    +============================+
                    |    ####################    |
                    |    #  [ RJ45 / ETH ]  #    |
                    |    ####################    |
                    +----------------------------+
                    |                            |
  (Enable)    EN ---|1 o                      o 1|--- IO39   (Input Only)
  (I2C/CFG) IO32 ---|2 o                      o 2|--- IO36   (Input Only)
 (RS485 EN) IO33 ---|3 o      [ ESP32 ]       o 3|--- IO15   (GPIO)
  (UART2 RX) IO5 ---|4 o                      o 4|--- IO14   (GPIO / ADC)
  (UART2 TX) IO17 ---|5 o    [ LAN8720A ]     o 5|--- IO12   (GPIO / ADC)
         GND ---|6 o                      o 6|--- IO35   (Input Only)
         3V3 ---|7 o                      o 7|--- IO4    (GPIO)
         GND ---|8 o                      o 8|--- IO2    (GPIO / Boot LED)
          5V ---|9 o                      o 9|--- GND
        LINK ---|10 o                    o 10|--- NC
                    |                            |
                    +----------------------------+
                    |  [ PROG ]                  |
                    |  TXD0  RXD0  IO0  GND      |
                    |    o     o    o    o        |
                    +============================+
```

**Left side** (pins 1–10) — Control & Power  
**Right side** (pins 1–10) — GPIO / Analog

> **Reserved / Internal GPIOs (do not use for general I/O):**
> | GPIO | Used For |
> |------|----------|
> | `GPIO 0`  | LAN8720 external oscillator |
> | `GPIO 16` | ETH PHY power — must be set `HIGH` to enable Ethernet |
> | `GPIO 18` | MDIO — Ethernet PHY management |
> | `GPIO 23` | MDC — Ethernet PHY management |
>
> **Input-Only:** IO35, IO36, IO39 — no output, no internal pull resistors.  
> **Power:** Use **either** 3V3 **or** 5V — never both at the same time.

## Project Structure

- `esp-extconn.ino`: Main project entry point.
- `ConfigHandler`: Manages the parsing of the internal JSON configuration.
- `DigitalHandler`: Logic for digital pins.
- `AnalogHandler`: Logic for analog and PWM pins.
- `CommHandler`: Logic for I2C, SPI, and UART.
- `SensorHandler`: Logic for ESP32-specific sensors.
- `NetworkHandler`: Logic for handling WiFi and Ethernet connectivity.
- `WebHandler`: Lightweight plain-HTML Web Server to configure the device.
- `SettingsHandler` & `EEPROMHandler`: Manages saving and loading dynamic App settings, web config arrays, and hardware configurations to persist flash EEPROM.
- `HardwareData.h`: The hardware configuration file defined as a JSON string.

## Setup Instructions

### 1. Configure Hardware
Edit the `HardwareData.h` file in the project folder. Change the `HARDWARE_CONFIG` string to match your wiring.
Example for ESP32:
```json
const char* HARDWARE_CONFIG = R"=====(
{
  "network": {
    "ethernet": {"enable": true},
    "wifi": {"enable": false, "ssid": "YOUR_WIFI_SSID", "password": "YOUR_WIFI_PASS"}
  },
  "digital": [
    {"pin": 2, "mode": "output", "name": "Built-in LED"},
    {"pin": 4, "mode": "input_pullup", "name": "Button 1"}
  ],
  "analog": [
    {"pin": 35, "mode": "input", "name": "ADC sensor"},
    {"pin": 12, "mode": "output", "channel": 0, "freq": 5000, "res": 8, "name": "PWM Output"}
  ],
  "comm": {
    "i2c": {"sda": 32, "scl": 33, "freq": 100000},
    "spi": {"sck": 14, "miso": 12, "mosi": 15, "ss": 4},
    "uart": [
      {"port": 2, "baud": 115200, "rx": 5, "tx": 17, "dataBits": 8, "parity": 0, "stopBits": 1}
    ]
  },
  "sensors": {
    "touch": [15, 14],
    "hall": true
  }
}
)=====";
```

### 2. Upload Code
1. Open `esp-extconn.ino` in the Arduino IDE.
2. Select your board (e.g., WT32-ETH01 or generic ESP32 Dev Module).
3. Click **Upload**.

(Note: You no longer need to upload external files to the device filesystem).

## Usage
Once booted, the ESP will:
1. Initialize the Serial monitor at **115200 baud**.
2. Initialize EEPROM and related settings.
3. Load the internal `HARDWARE_CONFIG` from memory.
4. Configure all defined pins and peripherals based on the JSON configuration.
5. If I2C is enabled, it will print a list of detected addresses to the console.
6. A Web Server stands up on Port 80.
   - If in AP mode (e.g., connected to "ESP-Config-XXXX"), your device will automatically show a Captive Portal prompting for login.
   - For all modes, going to the device IP displays the Default Status Page.
   - Accessing Settings requires the default password `admin1234` (configurable via the Web UI).

## Customization
To add custom logic for your specific sensors, you can modify the `loop()` function in `esp-extconn.ino` to read from the handlers using the simplified methods:
- `DigitalHandler::read(pin)`
- `AnalogHandler::read(pin)`
- `SensorHandler::readTouch(pin)`
