// #include <vector>
#include "gyroscope.h"

using std::vector;

std::vector<XYZ> GyroSensor::takeReadings() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // Adjusting for error using the offset calculated during caliberation
  XYZ acceleration = {
    x: a.acceleration.x - accel_offset.x,
    y: a.acceleration.y - accel_offset.y,
    z: a.acceleration.z - accel_offset.z,
  };
  
  XYZ gyro = {
    x: g.gyro.x - gyro_offset.x,
    y: g.gyro.y - gyro_offset.y,
    z: g.gyro.z - gyro_offset.z,
  };

  // float temperature = temp.temperature;

  return std::vector<XYZ>{acceleration, gyro};
}

void GyroSensor::printReadingsToSerial(XYZ &a, XYZ &g) {
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.x);
  Serial.print(", Y: ");
  Serial.print(a.y);
  Serial.print(", Z: ");
  Serial.print(a.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.x);
  Serial.print(", Y: ");
  Serial.print(g.y);
  Serial.print(", Z: ");
  Serial.print(g.z);
  Serial.println(" rad/s");

  // Serial.print("Temperature: ");
  // Serial.print(temp.temperature);
  // Serial.println(" degC");
}

bool GyroSensor::initialize() {
  bool failed = false;
  if (!mpu.begin()) {
    failed = true;
    Serial.println("Failed to find MPU6050 chip");
  }

  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
 
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  return !failed;
}

XYZ vecAverage(std::vector<XYZ>& vec) {
  XYZ res;

  for (int i = 0; i < vec.size(); i++) {
    res.x += vec[i].x;
    res.y += vec[i].y;
    res.z += vec[i].z;
  }

  res.x /= vec.size();
  res.y /= vec.size();
  res.z /= vec.size();

  return res;
}

void GyroSensor::caliberate() {
  // Delay so sensor can reach steady state (settle in).
  delay(3000);

  std::vector<XYZ> accel_readings;
  std::vector<XYZ> gyro_readings;

  Serial.println("Caliberating...");

  // Take 10 readings and use the average as the offset
  for (int i = 0; i < 10; i++) {
    auto readings = takeReadings();

    XYZ new_accel_reading = {
      x: readings[0].x,
      y: readings[0].y,
      z: readings[0].z - 9.8
    };
  
    XYZ new_gyro_reading = {
      x: readings[1].x,
      y: readings[1].y,
      z: readings[1].z
    };
    

    accel_readings.push_back(new_accel_reading);
    gyro_readings.push_back(new_gyro_reading);

    delay(3000);
    std::cout << "Count: " + std::to_string(i) << " - Acceleration: X - " << new_accel_reading.x << " Y - " << new_accel_reading.y << " Z - " << new_accel_reading.z << " - GYRO: X - " << new_gyro_reading.x << " Y - " << new_gyro_reading.y << " Z - " << new_gyro_reading.z << "\n"; 
  }

  XYZ mean_accel = vecAverage(accel_readings);
  XYZ mean_gyro = vecAverage(gyro_readings);

  accel_offset = mean_accel;
  gyro_offset = mean_gyro;

  std::cout << "Acceleration: X - " << mean_accel.x << " Y - " << mean_accel.y << " Z - " << mean_accel.z << "\n"; 
  std::cout << "GYRO: X - " << mean_gyro.x << " Y - " << mean_gyro.y << " Z - " << mean_gyro.z << "\n"; 
  Serial.println("Done Caliberating");
}