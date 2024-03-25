#include "ConfigurationWiFi.hpp"

ConfigurationWiFi configWiFi;

void setup() {
  
    Serial.begin(115200);
    configWiFi.begin();
}

void loop() {
    configWiFi.handleClient();
}
