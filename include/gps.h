#pragma once

#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <iostream>

// static const int TXPin = D5, RXPin = D6;
// static const int TXPin = D6, RXPin = D5;

// static TinyGPSPlus gps;

extern SoftwareSerial ss;

struct GPSReading {
  int satellites;
  float latitude;
  float longitude;
  // DateTime
  float speed; // in kmph
};

namespace GPS {
  void initialize(int baudrate = 9600);
  std::optional<GPSReading> takeGPSReading();
  void printGPSReading(GPSReading reading);
  // void print();
};
