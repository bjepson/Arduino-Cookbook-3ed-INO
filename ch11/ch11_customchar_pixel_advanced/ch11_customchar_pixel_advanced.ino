/*
 * customCharPixels
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//set constants for number of rows and columns to match your LCD
const int numRows = 2;
const int numCols = 16;

// array of bits defining pixels for 8 custom characters
// ones and zeros indicate if a pixel is on or off

byte glyphs[8][8]  = {
      {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B11111},   // 0
      {B00000,B00000,B00000,B00000,B00000,B00000,B11111,B11111},   // 1
      {B00000,B00000,B00000,B00000,B00000,B11111,B11111,B11111},   // 2
      {B00000,B00000,B00000,B00000,B11111,B11111,B11111,B11111},   // 3
      {B00000,B00000,B00000,B11111,B11111,B11111,B11111,B11111},   // 4
      {B00000,B00000,B11111,B11111,B11111,B11111,B11111,B11111},   // 5
      {B00000,B11111,B11111,B11111,B11111,B11111,B11111,B11111},   // 6
      {B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111}};  // 7

void setup ()
{
  lcd.begin(numCols, numRows);
  for(int i=0; i < 8; i++)
    lcd.createChar(i, glyphs[i]);     // create the custom glyphs
  lcd.clear();
}

void loop ()
{
  for(int i=0; i < 16; i++)
  {
    int value = analogRead(A0);
    value = map(value, 0, 1023, 0,16);
    doubleHeightBars(value, i); // show a value from 0 to 15
    delay(1000);  // one second interval between readings
  }
}

void doubleHeightBars(int value, int column)
{
  char upperGlyph;
  char lowerGlyph;

  if(value < 8)
  {
    upperGlyph = ' ';  // no pixels lit
    lowerGlyph = value;
  }
  else
  {
    upperGlyph = value - 8;
    lowerGlyph = 7; // all pixels lit
  }

  lcd.setCursor(column, 0); // do the upper half
  lcd.write(upperGlyph);
  lcd.setCursor(column, 1); // now to the lower half
  lcd.write(lowerGlyph);
}
