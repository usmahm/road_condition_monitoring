#pragma once

#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Extern usage - https://community.platformio.org/t/a-new-platformio-user-coding-wrong-getting-multiple-definition-first-defined-here-errors/14004/2
extern AsyncWebServer server;

void initializeWebServer();