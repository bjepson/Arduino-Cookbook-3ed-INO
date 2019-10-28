/*
 * Scroll
 * this sketch scrolls text left when tilted
 * text scrolls right when not tilted.
 */

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int numRows = 2;
const int numCols = 16;

const int tiltPin = 7; // pin connected to tilt sensor

const char textString[] = "tilt to scroll";
const int textLen = sizeof(textString) - 1; // the number of characters
bool isTilted = false;

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(numCols, numRows);
  pinMode(tiltPin, INPUT_PULLUP);
  lcd.print(textString);
}

void loop()
{
  if(digitalRead(tiltPin) == LOW && isTilted == false)
  {
    // here if tilted left so scroll text left
    isTilted = true;
    for (int position = 0; position  < textLen; position++)
    {
      lcd.scrollDisplayLeft();
      delay(150);
    }
  }
  if(digitalRead(tiltPin) == HIGH && isTilted == true)
  {
    // here if previously tilted but now flat, so scroll text right
    isTilted = false;
    for (int position = 0; position  < textLen; position++)
    {
      lcd.scrollDisplayRight();
      delay(150);
    }
  }
}
