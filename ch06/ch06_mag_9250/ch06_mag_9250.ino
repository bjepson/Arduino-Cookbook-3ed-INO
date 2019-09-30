/* Magnetometer sketch
   Read a magnetometer and display magnetic field strengths
*/

#include "MPU9250.h"
#include <math.h>

//  I2C address of IMU. If this doesn't work, try 0x69.
#define IMU_ADDRESS 0x68

MPU9250 IMU(Wire, IMU_ADDRESS); // Declare the IMU object

// Uncomment the next line to calibrate the magnetometer. You only need to do this once.
//#define RUN_CALIBRATION

void setup() {

  int status;

  Serial.begin(9600);
  while (!Serial);

  // Initialize the IMU
  status = IMU.begin();
  if (status < 0)
  {
    Serial.println("Could not initialize the IMU.");
    Serial.print("Error value: "); Serial.println(status);
    while (1); // halt the sketch
  }
#ifdef RUN_CALIBRATION
  Serial.println("When the countdown finishes, move the sensor in a figure 8 pattern.");
  Serial.print(3);
  for (int i = 2; i >= 0; i--)
  {
    Serial.print("..."); Serial.print(i);
    delay(1000);
  }
  Serial.println("\nMove the sensor in a figure 8 pattern until I tell you to stop.");
  status = IMU.calibrateMag();
  if (status < 0) {
    Serial.println("Failed to calibrate the magnetometer. Press reset and try again.");
  } else {
    Serial.println("Success!");
    Serial.println("Comment out #define RUN_CALIBRATION and upload the sketch again.");
  }
  Serial.println(IMU.getMagBiasX_uT());
  Serial.println(IMU.getMagScaleFactorX());
  Serial.println(IMU.getMagBiasY_uT());
  Serial.println(IMU.getMagScaleFactorY());
  Serial.println(IMU.getMagBiasZ_uT());
  Serial.println(IMU.getMagScaleFactorZ());
  while (1); // halt the sketch
#endif

  IMU.setMagCalX(10.13, 1.04);
  IMU.setMagCalY(34.14, 1.05);
  IMU.setMagCalZ(-64.76, 0.92);
}

void loop() {

  IMU.readSensor();

  // Obtain the magnetometer values across each axis in units of microTesla
  float mx = IMU.getMagX_uT();
  float my = IMU.getMagY_uT();
  float mz = IMU.getMagZ_uT();

  // From https://github.com/bolderflight/MPU9250/issues/33

  float m = sqrtf(mx * mx + my * my + mz * mz);
  mx /= m;
  my /= m;
  mz /= m;
  
  // Display the magnetometer values
  Serial.print("mx:");
  Serial.print(mx, 4);
  Serial.print(",my:");
  Serial.print(my, 4);
  Serial.print(",mz:");
  Serial.print(mz, 4);
  Serial.println();

  float calcAngle = constrainAngle360(atan2f(-my, mx)) * RAD_TO_DEG;
  Serial.print(calcAngle);
  Serial.println(" degrees");
  delay(100);
}

// From https://github.com/bolderflight/MPU9250/issues/33
float constrainAngle360(float dta) {
  dta = fmod(dta, 2.0 * PI);
  if (dta < 0.0)
    dta += 2.0 * PI;
  return dta - (14 * DEG_TO_RAD);
}
