#include "serialLogger.h"

void logger::print(auto data) {
  WebSerial.print(data);
  Serial.print(data);
}

void logger::println(auto data) {
  WebSerial.println(data);
  Serial.println(data);
}

void parseReceivedMsg(uint8_t *data, size_t len) {
  String d = "";
  
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  
  WebSerial.println(d);

  // if (d == "ON"){
  //   digitalWrite(LED, LOW);
  // }
  // if (d=="OFF"){
  //   digitalWrite(LED, HIGH);
  // }
}

void initializeSerialLogger() {
  WebSerial.begin(&server);
  WebSerial.msgCallback(parseReceivedMsg);
  logger::println("DONE INIT");
}