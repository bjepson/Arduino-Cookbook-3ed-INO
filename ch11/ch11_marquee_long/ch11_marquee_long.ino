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

// this version of marquee uses manual scrolling for very long messages
void marquee(char *text)
{
  int length = strlen(text); // the number of characters in the text
  if(length < numCols)
    lcd.print(text);
  else
  {
    int pos;
    for(pos = 0; pos < numCols; pos++)
       lcd.print(text[pos]);
    delay(1000); // allow time to read the first line before scrolling
    pos=1;
    while(pos <= length - numCols)
    {
      lcd.setCursor(0,0);
      for(int i=0; i < numCols; i++)
        lcd.print(text[pos+i]);
      delay(300);
      pos = pos + 1;
    }
  }
}
