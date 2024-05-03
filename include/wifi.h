#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
// #include <ESPAsyncTCP.h>
// #include <ESPAsyncWebServer.h>

bool initializeWifi(bool keep_retrying=true);