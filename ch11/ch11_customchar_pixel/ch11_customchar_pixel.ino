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
  for( byte i=0; i < 8; i++)
    lcd.write(i);   // show all eight single height bars
  delay(2000);
  lcd.clear();
}
