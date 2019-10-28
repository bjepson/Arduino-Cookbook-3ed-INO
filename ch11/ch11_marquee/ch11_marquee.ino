/*
 * Marquee
 * this sketch can scroll a very long line of text
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int numRows = 2;
const int numCols = 16;

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(numCols, numRows);
  marquee("This is a very long string of text that will scroll");
}

void loop()
{
}

// this function uses scrolling to display a message up to 32 bytes long
void marquee(char *text)
{  
  lcd.print(text);
  delay(1000);
  for (int position = 0; position < strlen(text)-numCols; position++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }    
}
