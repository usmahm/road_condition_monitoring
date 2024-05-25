#include "webServer.h"

AsyncWebServer server(80);

void initializeWebServer() {
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}