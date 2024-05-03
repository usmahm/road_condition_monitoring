#pragma once

#include <Arduino.h>
#include <vector>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// void initializeGyroscope();

// std::vector<sensors_event_t *> takeGyroscopeReading();

// void uploadGyroscopeReading(sensors_event_t* acceleration, sensors_event_t* gyro);
struct XYZ {
  public:
    float X() { return x_; }
    float Y() { return y_; }
    float Z() { return z_; }
    void X(float x) { x_ = x; }
    void Y(float y) { y_ = y; }
    void Z(float z) { z_ = z; }
  private:
    float x_{0.};
    float y_{0.};
    float z_{0.};
};

class GyroSensor {
  public:
    std::vector<sensors_event_t> takeReadings();
    void printReadingsToSerial(sensors_event_t &a, sensors_event_t &g, sensors_event_t &temp);

    // Returns true if initialized successfully
    bool initialize();
    void caliberate();
    // GyroSensor();

  private:
    Adafruit_MPU6050 mpu;

    XYZ accel_offset;
    XYZ gyro_offset;
};