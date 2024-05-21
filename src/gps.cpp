#include "gps.h"

static const int TXPin = D6, RXPin = D5;

static TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);


void GPS::initialize(int baudrate) {
  CustomLogger::println("Initializing GPS Module");
  ss.begin(baudrate);

  // To check GPS connection
  // gps.encode encodes and increment charsProcessed if connection is correct
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < 1000);
  
  if (gps.charsProcessed() < 10) {
    CustomLogger::println (F("No GPS detected: check wiring."));
  }
}


std::optional<GPSReading> GPS::takeGPSReading() {
  // delay(5000);
  if (ss.available() > 0) {
    gps.encode(ss.read());
  }

  if (gps.location.isValid() && gps.satellites.isValid() && gps.speed.isValid()) {

    // Note: lat and lng returns previous values read even when sattellites in view = 0 (To be handled it later)
    GPSReading reading(
      gps.satellites.value(),
      gps.location.lat(),
      gps.location.lng(),
      gps.speed.kmph()
    );

    return reading;
  } else {
    if (gps.satellites.isValid()) {
      CustomLogger::print("satellites: ");
      CustomLogger::println(gps.satellites.value());
    }
  }

  return std::nullopt;
}

void GPS::printGPSReading(GPSReading reading) {
  std::cout << "Satellites: " << reading.satellites << " Latitude: " << reading.latitude << " Longitude: " << reading.longitude << " Speed: " << reading.speed << "\n";
}