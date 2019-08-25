/*
  Arduino LSM6DS3 - Simple Accelerometer

  This example reads the acceleration values from the LSM6DS3
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  //  Serial.print("Accelerometer sample rate = ");
  //  Serial.print(IMU.accelerationSampleRate());
  //  Serial.println(" Hz");
  //  Serial.println();
  //  Serial.println("Acceleration in G's");
  //  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    Serial.print("{");
    Serial.print("'x': "); Serial.print(x); Serial.print(", ");
    Serial.print("'y': "); Serial.print(y); Serial.print(", ");
    Serial.print("'z': "); Serial.print(z); Serial.print(", ");
    Serial.println("}");
    delay(200);
  }
}
