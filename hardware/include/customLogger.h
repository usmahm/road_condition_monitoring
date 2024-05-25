#pragma once

#include <Arduino.h>
#include <WebSerial.h>
#include "webServer.h"

namespace CustomLogger {
  template <typename T>
  void print(T data) {
    WebSerial.print(data);
    Serial.print(data);
  };

  template <typename T>
  void println(T data) {
    WebSerial.println(data);
    Serial.println(data);
  };
  
  void initializeSerialLogger();
  void parseReceivedMsg(uint8_t *data, size_t len);
}
