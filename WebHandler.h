#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>
#include "SettingsHandler.h"

class WebHandler {
public:
    static void setup();
    static void loop();

private:
    static WebServer server;
    static void handleStatus();
    static void handleRoot();
    static void handleSave();
    static void handleLogin();
    static void handleAuth();
    static bool checkAuth();
    static void captivePortalRedirect();
};

#endif
