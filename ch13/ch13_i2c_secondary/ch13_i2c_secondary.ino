/*
 * I2C Secondary sketch
 * monitors I2C requests and echoes these to the serial port
 */

#include <Wire.h>

const int address = 4;  // the address to be used by the communicating devices

void setup()
{
  Serial.begin(9600);
  Wire.begin(address); // join I2C bus using this address
  Wire.onReceive(receiveEvent); // register event to handle requests
}

void loop()
{
  // nothing here--all the work is done in receiveEvent
}

void receiveEvent(int howMany)
{
  while(Wire.available() > 0)
  {
    char c = Wire.read(); // receive byte as a character
    Serial.write(c); // echo
  }
}
