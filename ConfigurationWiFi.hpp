#ifndef CONFIGURATION_WIFI_HPP
#define CONFIGURATION_WIFI_HPP

#include <Preferences.h>
#include <WiFi.h>
#include <WebServer.h>


class ConfigurationWiFi {
public:
    ConfigurationWiFi();
    void begin();
    void handleClient();
    

    Preferences pref;
    WebServer server;
    const char* apSSID;
    const char* apPassword;
    String ssidd;
    String passwordd;
    void handleRoot();
    void handleSave();
};

#endif
