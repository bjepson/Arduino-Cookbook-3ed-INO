/*
 * LiquidCrystal Library - Hello World
 *
 * Demonstrates the use of a 16 × 2 LCD display.
 * https://www.arduino.cc/en/Tutorial/HelloWorld
 */

#include <LiquidCrystal.h> // include the library code

//constants for the number of rows and columns in the LCD
const int numRows = 2;
const int numCols = 16;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(numCols, numRows);
  lcd.print("Hello, World!");  // Print a message to the LCD.
}

void loop()
{
  // set the cursor to column 0, line 1
  // (row numbering starts with 0, so line 1 is the second row):
  lcd.setCursor(0, 1);
  // print the number of seconds since the sketch started:
  lcd.print(millis()/1000);
}
