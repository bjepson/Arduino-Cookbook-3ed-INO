/*
 * I2C Master w/print sketch
 * Sends sensor data to an I2C secondary using print
 */

#include <Wire.h>

const int address = 4;     // the address to be used by the communicating devices
const int sensorPin = A0;  // select the analog input pin for the sensor
int val;                   // variable to store the sensor value

void setup()
{
  Wire.begin();
}

void loop()
{
  val = analogRead(sensorPin);       // read the voltage on the pot 
                                     // (val ranges from 0 to 1023)
  Wire.beginTransmission(address); // transmit to device
  Wire.println(val);
  Wire.endTransmission();
  delay(1000);
}
