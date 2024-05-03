#pragma once
#include <Arduino.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// void initializeGyroscope();

// std::vector<sensors_event_t *> takeGyroscopeReading();

// void uploadGyroscopeReading(sensors_event_t* acceleration, sensors_event_t* gyro);

class GyroSensor {
  public:
    std::vector<sensors_event_t> takeReadings();
    void printReadingsToSerial(sensors_event_t &a, sensors_event_t &g, sensors_event_t &temp);

    // Returns true if initialized successfully
    bool initialize();
    // GyroSensor();

  private:
    Adafruit_MPU6050 mpu;
};