/*
 * LiquidCrystal Library - Special Chars
 */

#include <LiquidCrystal.h>

//set constants for number of rows and columns to match your LCD
const int numRows = 2;
const int numCols = 16;

// defines for some useful symbols
const byte degreeSymbol = B11011111;
const byte piSymbol     = B11110111;
const byte centsSymbol  = B11101100;
const byte sqrtSymbol   = B11101000;
const byte omegaSymbol  = B11110100;  // the symbol used for ohms

byte charCode = 32; // the first printable ascii character
int col;
int row;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(numRows, numCols);

  showSymbol(degreeSymbol, "degrees");
  showSymbol(piSymbol,     "pi");
  showSymbol(centsSymbol,  "cents");
  showSymbol(sqrtSymbol,   "sqrt");
  showSymbol(omegaSymbol,  "ohms");
  lcd.clear();

}

void loop()
{
  lcd.write(charCode);
  calculatePosition();
  if(charCode == 255)
  {
    // finished all characters so wait another few seconds and start over
    delay(2000);
    lcd.clear();
    row = col = 0;
    charCode = 32;
  }
  charCode = charCode + 1;
}

void calculatePosition()
{
  col = col + 1;
  if( col == numCols)
  {
    col = 0;
    row = row + 1;
    if( row == numRows)
    {
      row = 0;
      delay(2000); // pause
      lcd.clear();
    }
    lcd.setCursor(col, row);
  }
}

// function to display a symbol and its description
void showSymbol(byte symbol, char *description)
{
  lcd.clear();
  lcd.write(symbol);
  lcd.print(' '); // add a space before the description
  lcd.print(description);
  delay(3000);
}
