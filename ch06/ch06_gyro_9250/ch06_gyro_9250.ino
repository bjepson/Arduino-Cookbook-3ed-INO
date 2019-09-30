/* Gyro sketch
 * Read a gyro and display rotation in degrees/sec
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

  // Set the full range of the gyro to +/- 500 degrees/sec
  status = IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  if (status < 0) {
    Serial.println("Could not change gyro range.");
    Serial.print("Error value: "); Serial.println(status);
  }
}

void loop() {

  IMU.readSensor();

  // Obtain the rotational velocity in rads/second
  float gx = IMU.getGyroX_rads();
  float gy = IMU.getGyroY_rads();
  float gz = IMU.getGyroZ_rads();

  // Display velocity in degrees/sec
  Serial.print("gx:");
  Serial.print(gx * RAD_TO_DEG, 4);
  Serial.print(",gy:");
  Serial.print(gy * RAD_TO_DEG, 4);
  Serial.print(",gz:");
  Serial.print(gz * RAD_TO_DEG, 4);
  Serial.println();
  delay(100);
}
