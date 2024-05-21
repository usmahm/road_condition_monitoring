#include <Arduino.h>
#include "gyroscope.h"
#include "wifi.h"
#include "webServer.h"
#include "customLogger.h"
#include "gps.h"

int baudrate = 9600;
GyroSensor gs;

void setup() {
  Serial.begin(baudrate);
  while (!Serial) {
    delay(10);
  }

  initializeWifi();
  initializeWebServer();
  
  CustomLogger::initializeSerialLogger();
  
  CustomLogger::println("RUNNING");

  if (!gs.initialize()) {
    while (1) {
      delay(10);
    }
  }

  gs.caliberate();

  GPS::initialize(baudrate);

  CustomLogger::println("");
  delay(100);
}

void loop() {
  auto gyroReadings = gs.takeReadings();
  
  gs.printReadingsToSerial(gyroReadings[0], gyroReadings[1]);

  auto gpsReading = GPS::takeGPSReading();
  if (gpsReading) {
    // GPS::print();
    GPS::printGPSReading(*gpsReading);
  } else {
    CustomLogger::print("Invalid GPS Reading");
  }
  
  // uploadGyroscopeReading(readings[0], readings[1]);

  CustomLogger::println("");
  delay(1000);
}
