#pragma once

#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <iostream>
#include "customLogger.h"

extern SoftwareSerial ss;

struct GPSReading {
  uint32_t satellites;
  double latitude;
  double longitude;
  // DateTime
  double speed; // in kmph

  GPSReading(uint32_t s, double lat, double lng, double sp) : satellites(s), latitude(lat), longitude(lng), speed(sp) {}
};

namespace GPS {
  void initialize(int baudrate = 9600);
  std::optional<GPSReading> takeGPSReading();
  void printGPSReading(GPSReading reading);
  // void print();
};
