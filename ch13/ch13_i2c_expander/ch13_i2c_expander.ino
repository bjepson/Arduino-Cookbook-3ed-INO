/*
 * I2C bargraph sketch
 * Uses I2C port to drive a bar graph
 * Turns on a series of LEDs proportional to a value of an analog sensor.
 * see #sequencing_multiple_leds_colon_creati
 */

#include <Wire.h>

const int address = 0x20; // PCF8574 address; use 0x38 for PCF8574A
const int NbrLEDs = 8;

const int analogInPin = A0; // Analog input pin connected
// to a variable resistor

int sensorValue = 0;    // value read from the sensor
int ledLevel = 0;       // sensor value converted into LED 'bars'
int ledBits = 0;        //  bits for each LED will be set to 1 to turn on LED

void setup()
{
  Wire.begin(); // set up Arduino I2C support
}

void loop()
{
  sensorValue = analogRead(analogInPin);             // read the analog value
  ledLevel = map(sensorValue, 0, 1023, 0, NbrLEDs);  // map to number of LEDs
  for (int led = 0; led < NbrLEDs; led++)
  {
    Wire.beginTransmission(address);
    if (led < ledLevel)
    {
      Wire.write(~ (1 << led));
    }
    else
    {
      Wire.write(0xFF); // Turn off all LEDs
    }
    Wire.endTransmission(); // send the value to I2C
  }
}
