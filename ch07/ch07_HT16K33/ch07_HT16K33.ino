/*
  HT16K33 seven segment display sketch
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

const int numberOfDigits = 4; // change this to match the number of digits wired up
const int maxCount       = 9999;

int number = 0;

void setup()
{
  Serial.begin(9600);
  matrix.begin(0x70);     // Initialize the display
  matrix.println(number); // Send the number (0 initially) to the display
  matrix.writeDisplay();  // Update the display
}

void loop()
{
  // display a number from serial port terminated by end of line character
  if (Serial.available())
  {
    char ch  = Serial.read();
    if ( ch == '\n')
    {
      if (number <= maxCount)
      {
        matrix.println(number);
        matrix.writeDisplay();
        number = 0; // Reset the number to 0
      }
    }
    else
      number = (number * 10) + ch - '0'; // see Chapter 4 for details
  }
}
