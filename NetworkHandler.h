#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ETH.h>
#include <DNSServer.h>
#include "SettingsHandler.h"

class NetworkHandler {
public:
    static bool forceOTA;
    static void setup();
    static void loop();
    static void handleWiFi();
    static void handleEthernet();
    static void onEvent(WiFiEvent_t event);
    static bool eth_connected;
private:
    static DNSServer dnsServer;
};

#endif
