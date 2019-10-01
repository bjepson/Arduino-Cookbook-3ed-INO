/* SensorFusion sketch
 * Interpret 9DOF sensor data into pitch, roll, and yaw 
 */

#include "MPU9250.h" 	
#include "SensorFusion.h"
#include "EEPROM.h"

SF fusion;

float gx, gy, gz, ax, ay, az, mx, my, mz, temp;
float pitch, roll, yaw;
float deltat;

//  I2C address of IMU. If this doesn't work, try 0x69.
#define IMU_ADDRESS 0x68
MPU9250 IMU(Wire, IMU_ADDRESS); // Declare the IMU object

int status;

void setup() {

  Serial.begin(115200);
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

  ax = IMU.getAccelX_mss();
  ay = IMU.getAccelY_mss();
  az = IMU.getAccelZ_mss();
  gx = IMU.getGyroX_rads();
  gy = IMU.getGyroY_rads();
  gz = IMU.getGyroZ_rads();
  mx = IMU.getMagX_uT();
  my = IMU.getMagY_uT();
  mz = IMU.getMagZ_uT();

  deltat = fusion.deltatUpdate();

  fusion.MadgwickUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);

  roll = fusion.getRollRadians();
  pitch = fusion.getPitchRadians();
  yaw = fusion.getYawRadians();

  Serial.print(pitch); Serial.print(":");
  Serial.print(roll);  Serial.print(":");
  Serial.println(yaw);

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
