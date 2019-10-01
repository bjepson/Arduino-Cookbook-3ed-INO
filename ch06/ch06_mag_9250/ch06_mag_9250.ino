/* Magnetometer sketch
   Read a magnetometer and display magnetic field strengths
*/

#include "MPU9250.h"
#include <math.h>
#include "EEPROM.h"

//  I2C address of IMU. If this doesn't work, try 0x69.
#define IMU_ADDRESS 0x68

// Change this to the declination for your location. See https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml
#define DECLINATION (-14)

MPU9250 IMU(Wire, IMU_ADDRESS); // Declare the IMU object

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
  
  load_calibration();
}

void loop() {

  IMU.readSensor();

  // Obtain the magnetometer values across each axis in units of microTesla
  float mx = IMU.getMagX_uT();
  float my = IMU.getMagY_uT();
  float mz = IMU.getMagZ_uT();

  // From https://github.com/bolderflight/MPU9250/issues/33
  // Normalize the magnetometer data.
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

  float constrained = constrainAngle360(atan2f(-my, mx) + (DECLINATION * DEG_TO_RAD));
  float calcAngle = constrained * RAD_TO_DEG;
  Serial.print(calcAngle);
  Serial.println(" degrees");
  delay(100);
}

// From https://github.com/bolderflight/MPU9250/issues/33
float constrainAngle360(float dta) {
  dta = fmod(dta, 2.0 * PI);
  if (dta < 0.0)
    dta += 2.0 * PI;
  return dta;
}

// Load the calibration from the eeprom
// From https://github.com/bolderflight/MPU9250/issues/33
void load_calibration() {
  float hxb, hxs, hyb, hys, hzb, hzs;

  uint8_t eeprom_buffer[24];
  for (unsigned int i = 0; i < sizeof(eeprom_buffer); i++ ) {
    eeprom_buffer[i] = EEPROM.read(i);
  }
  memcpy(&hxb, eeprom_buffer, sizeof(hxb));
  memcpy(&hyb, eeprom_buffer + 4, sizeof(hyb));
  memcpy(&hzb, eeprom_buffer + 8, sizeof(hzb));
  memcpy(&hxs, eeprom_buffer + 12, sizeof(hxs));
  memcpy(&hys, eeprom_buffer + 16, sizeof(hys));
  memcpy(&hzs, eeprom_buffer + 20, sizeof(hzs));
  IMU.setMagCalX(hxb, hxs);
  IMU.setMagCalY(hyb, hys);
  IMU.setMagCalZ(hzb, hzs);
}
