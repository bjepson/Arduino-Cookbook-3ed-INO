/*
 * LiquidCrystal Library - FormatText
 */

#include <LiquidCrystal.h> // include the library code:

//constants for the number of rows and columns in the LCD
const int numRows = 2;
const int numCols = 16;

int count;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(numCols, numRows);
  lcd.print("Starting in ");  // this string is 12 characters long
  for(int i=9; i > 0; i--)    // count down from 9
  {
    // the top line is row 0
    lcd.setCursor(12,0); // move the cursor to the end of the string
    lcd.print(i);
    delay(1000);
  }
}

void loop()
{
int columnWidth = 4;
int displayColumns = numCols / columnWidth;

  lcd.clear();
  for(int row=0; row < numRows; row++)
  {
    for( int col=0; col < displayColumns; col++)
    {
      lcd.setCursor(col * columnWidth, row);
      count = count+ 1;
      lcd.print(count);
    }
  }
  delay(1000);
}
