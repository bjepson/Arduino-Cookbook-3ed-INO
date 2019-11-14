/*
 * I2C_Master
 * Echo Serial data to an I2C secondary
 */

#include <Wire.h>

const int address = 4;  // the address to be used by the communicating devices

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  char c;
  if(Serial.available() > 0)
  {
    c = Serial.read();
    // send the data
    Wire.beginTransmission(address); // transmit to device
    Wire.write(c);
    Wire.endTransmission();
  }
}
