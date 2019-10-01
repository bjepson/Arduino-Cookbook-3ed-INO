/* Accelerometer sketch
 * Read a accelerometer and display acceleration in m/s/s 
 */

#include "MPU9250.h"

//  I2C address of IMU. If this doesn't work, try 0x69.
#define IMU_ADDRESS 0x68

MPU9250 IMU(Wire, IMU_ADDRESS); // Declare the IMU object

void setup() {

  Serial.begin(9600);
  while(!Serial);

  // Initialize the IMU
  int status = IMU.begin();
  if (status < 0) {
    Serial.println("Could not initialize the IMU.");
    Serial.print("Error value: "); Serial.println(status);
    while(1); // halt the sketch
  }

}

void loop() {

  IMU.readSensor();

  // Obtain the rotational velocity in rads/second
  float ax = IMU.getAccelX_mss();
  float ay = IMU.getAccelY_mss();
  float az = IMU.getAccelZ_mss();

  // Display velocity in degrees/sec
  Serial.print("ax:");  Serial.print(ax, 4);
  Serial.print(",ay:"); Serial.print(ay, 4);
  Serial.print(",az:"); Serial.print(az, 4);
  Serial.println();
  delay(100);
}
