#include "wifi.h"
// #include "serialLogger.h"

const char* ssid = WIFISSID;
const char* password = WIFI_PASSWORD;

bool initializeWifi(bool keep_retrying) {
  Serial.println("Initializing WIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  if (keep_retrying) {
    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
  } else {
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed!\n");
      return false;
    }
  }

  return true;
}
