#include "wifi_manager.h"

void WiFiManager::init() {
  WiFi.begin(WiFi_SSID, WiFi_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network: " + WiFi.localIP().toString());
}
