#include "CommHandler.h"
#include "SettingsHandler.h"

void CommHandler::setup(JsonObject comms) {
    // I2C
    if (comms.containsKey("i2c")) {
        JsonObject i2c = comms["i2c"];
        int sda = i2c["sda"] | -1;
        int scl = i2c["scl"] | -1;
        uint32_t freq = i2c["freq"] | 100000;
        
        if (sda != -1 && scl != -1) {
            Wire.begin(sda, scl);
            Wire.setClock(freq);
            Serial.println("I2C Initialized");
        }
    }

    // SPI
    if (comms.containsKey("spi")) {
        JsonObject spi = comms["spi"];
        int sck = spi["sck"] | -1;
        int miso = spi["miso"] | -1;
        int mosi = spi["mosi"] | -1;
        int ss = spi["ss"] | -1;
        
        if (sck != -1 && miso != -1 && mosi != -1) {
            SPI.begin(sck, miso, mosi, ss);
            Serial.println("SPI Initialized");
        }
    }

    // UART
    if (comms.containsKey("uart")) {
        JsonArray uarts = comms["uart"];
        int index = 0;
        for (JsonObject u : uarts) {
            int port = u["port"] | 1;
            long baud = u["baud"] | 9600;
            int rx = u["rx"] | -1;
            int tx = u["tx"] | -1;
            
            // Check EEPROM for overrides
            uint32_t config = SERIAL_8N1;
            if (SettingsHandler::settings.uart.port == port) {
                baud = SettingsHandler::settings.uart.baudrate;
                config = SettingsHandler::getSerialConfig(SettingsHandler::settings.uart.dataBits, SettingsHandler::settings.uart.parity, SettingsHandler::settings.uart.stopBits);
                Serial.print("UART "); Serial.print(port); Serial.println(" loaded from EEPROM global settings");
            } else {
                // Use JSON defaults
                int db = u["dataBits"] | 8;
                int pr = u["parity"] | 0; // 0:None, 1:Odd, 2:Even
                int sb = u["stopBits"] | 1;
                config = SettingsHandler::getSerialConfig(db, pr, sb);
                Serial.print("UART "); Serial.print(port); Serial.println(" using JSON defaults");
            }

            if (port == 1) {
                Serial1.begin(baud, config, rx, tx);
            } else if (port == 2) {
                Serial2.begin(baud, config, rx, tx);
            }
            index++;
        }
    }
}

void CommHandler::i2cScan() {
    byte error, address;
    int nDevices = 0;
    Serial.println("Scanning I2C...");
    for(address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");
            nDevices++;
        }
    }
    if (nDevices == 0) Serial.println("No I2C devices found\n");
}

void CommHandler::uartSend(int port, const char* data) {
    if (port == 1) Serial1.print(data);
    else if (port == 2) Serial2.print(data);
}
