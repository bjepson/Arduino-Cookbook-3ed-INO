/*
   Accelerometer to JSON. Sends JSON-formatted representation of
   accelerometer readings.
*/

#include <Arduino_LSM6DS3.h>   // Arduino WiFi R2
//#include <Arduino_LSM9DS1.h> // Arduino BLE Sense

//FIXME: does this work with breakout boards as well?

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    while (1) {
      Serial.println("Error: Failed to initialize IMU");
      delay(3000);
    }
  }
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
    delay(1000);
  }

}
