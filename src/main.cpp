#include <Arduino.h>
#include "gyroscope.h"
#include "wifi.h"
#include "webServer.h"

GyroSensor gs;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Serial.println("");


  initializeWifi();
  initializeWebServer();

  if (!gs.initialize()) {
    while (1) {
      delay(10);
    }
  }

  // gs.caliberate();

  Serial.println("");
  delay(100);
}

void loop() {
  std::vector<sensors_event_t> readings = gs.takeReadings();
  
  gs.printReadingsToSerial(readings[0], readings[1], readings[2]);
  // uploadGyroscopeReading(readings[0], readings[1]);

  Serial.println("");
  delay(500);
}
