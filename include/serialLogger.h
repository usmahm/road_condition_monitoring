#pragma once

#include <Arduino.h>
#include <WebSerial.h>
#include "webServer.h"

namespace logger {
  void print(auto data);
  void println(auto data);
}

void initializeSerialLogger();
void parseReceivedMsg(uint8_t *data, size_t len);