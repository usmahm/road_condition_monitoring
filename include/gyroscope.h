#pragma once

#include <Arduino.h>
#include <vector>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <numeric>
#include <string>
#include <iostream>
#include "customLogger.h"

// void initializeGyroscope();

// std::vector<sensors_event_t *> takeGyroscopeReading();

// void uploadGyroscopeReading(sensors_event_t* acceleration, sensors_event_t* gyro);
struct XYZ {
  // public:
  //   float X() { return x_; }
  //   float Y() { return y_; }
  //   float Z() { return z_; }
  //   void X(float x) { x_ = x; }
  //   void Y(float y) { y_ = y; }
  //   void Z(float z) { z_ = z; }
  // private:
    float x{0.};
    float y{0.};
    float z{0.};
};

class GyroSensor {
  public:
    std::vector<XYZ> takeReadings();
    void printReadingsToSerial(XYZ &a, XYZ &g);

    // Returns true if initialized successfully
    bool initialize();
    void caliberate();
    // GyroSensor();

  private:
    Adafruit_MPU6050 mpu;

    XYZ accel_offset;
    XYZ gyro_offset;
};