#include "NetworkHandler.h"

bool NetworkHandler::eth_connected = false;
bool NetworkHandler::forceOTA = false;
DNSServer NetworkHandler::dnsServer;

void NetworkHandler::onEvent(WiFiEvent_t event) {
    switch (event) {
        case ARDUINO_EVENT_ETH_START:
            Serial.println("ETH Started");
            ETH.setHostname("esp32-eth01");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            Serial.println("ETH Connected");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            Serial.print("ETH MAC: ");
            Serial.print(ETH.macAddress());
            Serial.print(", IPv4: ");
            Serial.print(ETH.localIP());
            if (ETH.fullDuplex()) {
                Serial.print(", FULL_DUPLEX");
            }
            Serial.print(", ");
            Serial.print(ETH.linkSpeed());
            Serial.println("Mbps");
            eth_connected = true;
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            Serial.println("ETH Disconnected");
            eth_connected = false;
            break;
        case ARDUINO_EVENT_ETH_STOP:
            Serial.println("ETH Stopped");
            eth_connected = false;
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.print("WiFi Connected. IP Address: ");
            Serial.println(WiFi.localIP());
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            Serial.println("WiFi Disconnected");
            break;
        case ARDUINO_EVENT_WIFI_AP_START:
            Serial.println("WiFi AP Started");
            Serial.print("AP IP Address: ");
            Serial.println(WiFi.softAPIP());
            break;
        default:
            break;
    }
}

void NetworkHandler::setup() {
    WiFi.onEvent(onEvent);

    handleEthernet();
    handleWiFi();
}

void NetworkHandler::loop() {
    if (SettingsHandler::settings.wifi_mode == 1 || forceOTA) {
        dnsServer.processNextRequest();
    }
}

void NetworkHandler::handleEthernet() {
    Serial.println("Initializing WT32-ETH01 Ethernet...");
    // WT32-ETH01 specific PHY setup
    // ESP32 core v3.x ETH.begin() signature:
    // begin(eth_phy_type_t type, int32_t phy_addr, int mdc, int mdio, int power, eth_clock_mode_t clk_mode)
    if (!ETH.begin(ETH_PHY_LAN8720, 1, 23, 18, 16, ETH_CLOCK_GPIO0_IN)) {
        Serial.println("Ethernet initialization failed!");
        return;
    }
    
    if (SettingsHandler::settings.eth_dhcp == 0) {
        IPAddress ip, gw, mask;
        ip.fromString(SettingsHandler::settings.eth_ip);
        gw.fromString(SettingsHandler::settings.eth_gw);
        mask.fromString(SettingsHandler::settings.eth_mask);
        ETH.config(ip, gw, mask, gw);
        Serial.println("Ethernet Static IP Configured.");
    } else {
        Serial.println("Ethernet DHCP Enabled.");
    }
}

void NetworkHandler::handleWiFi() {
    if (SettingsHandler::settings.wifi_mode == 1 || forceOTA) {
        // AP Mode
        Serial.println("Starting WiFi AP Mode...");
        WiFi.mode(WIFI_AP);
        String apName = "ESP-Config-" + String((uint32_t)ESP.getEfuseMac(), HEX);
        WiFi.softAP(apName.c_str(), "");
        dnsServer.start(53, "*", WiFi.softAPIP());
    } else {
        // STA Mode
        if (strlen(SettingsHandler::settings.wifi_ssid) > 0) {
            Serial.print("Connecting to WiFi: ");
            Serial.println(SettingsHandler::settings.wifi_ssid);
            WiFi.mode(WIFI_STA);
            WiFi.begin(SettingsHandler::settings.wifi_ssid, SettingsHandler::settings.wifi_pass);
        } else {
            Serial.println("WiFi STA enabled but no SSID provided");
        }
    }
}
