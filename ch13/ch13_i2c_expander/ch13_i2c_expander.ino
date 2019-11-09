/*
 * I2C bargraph sketch
 * Uses I2C port to drive a bar graph
 * Turns on a series of LEDs proportional to a value of an analog sensor.
 * see #sequencing_multiple_leds_colon_creati
*/

#include <Wire.h>

const int address = 0x20; // Default address for PCF8574
//const int address = 0x20; // Default address for PCF8574A
const int NbrLEDs = 8;

void setup()
{
  Wire.begin(); // set up Arduino I2C support
  Serial.begin(9600);

  Wire.beginTransmission(address);
  Wire.write(0xFF);
  Wire.endTransmission();
}

byte led = 1; // Current LED
int direction = 1; // Incrementing or decrementing?

void loop()
{
  if (direction == 1)
    led <<= 1; // Shift left
  else
    led >>= 1; // Shift right
    
  if (led >= 128 || led <= 1)
  {
    direction *= -1;
  }
  Wire.beginTransmission(address);
  Wire.write(~led);
  Serial.println(led, BIN);
  Wire.endTransmission();
  delay(200);

}
