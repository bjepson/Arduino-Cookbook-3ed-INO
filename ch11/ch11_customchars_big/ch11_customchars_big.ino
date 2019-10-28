/*
 * customChars
 * This sketch displays double-height digits
 * the bigDigit arrays were inspired by Arduino forum member dcb
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte glyphs[5][8] = {
  { B11111,B11111,B00000,B00000,B00000,B00000,B00000,B00000 },
  { B00000,B00000,B00000,B00000,B00000,B00000,B11111,B11111 },
  { B11111,B11111,B00000,B00000,B00000,B00000,B11111,B11111 },
  { B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111 } ,
  { B00000,B00000,B00000,B00000,B00000,B01110,B01110,B01110 } };

const int digitWidth = 3; // the width in characters of a big digit 
                          // (excludes space between characters)

//arrays  to index into custom characters that will comprise the big numbers
// digits 0 - 4                             0      1       2      3      4
const char bigDigitsTop[10][digitWidth]={ 3,0,3, 0,3,32, 2,2,3, 0,2,3, 3,1,3,
// digits 5-9                               5      6      7        8      9
                                          3,2,2, 3,2,2, 0,0,3,   3,2,3, 3,2,3};

const char bigDigitsBot[10][ digitWidth]={ 3,1,3, 1,3,1,  3,1,1, 1,1,3, 32,32,3,
                                           1,1,3, 3,1,3, 32,32,3, 3,1,3, 1,1,3};

char buffer[12]; // used to convert a number into a string
void setup ()
{
  lcd.begin(20,4);
  // create the custom glyphs
  for(int i=0; i < 5; i++)
    lcd.createChar(i, glyphs[i]); // create the 5 custom glyphs
  // show a countdown timer
  for(int digit = 9; digit >= 0; digit--)
  {
    showDigit(digit, 0);  // show the digit
    delay(1000);
  }
  lcd.clear();
}

void loop ()
{
  // now show the number of seconds since the sketch started
  int number = millis() / 1000;
  showNumber(number, 0);
  delay(1000);
  Serial.begin(9600);
}

void showDigit(int digit, int position)
{
  lcd.setCursor(position * (digitWidth + 1), 0);
  for(int i=0; i < digitWidth; i++)
    lcd.write(bigDigitsTop[digit][i]);
  lcd.setCursor(position * (digitWidth + 1), 1);
  for(int i=0; i < digitWidth; i++)
    lcd.write(bigDigitsBot[digit][i]);
}

void showNumber(int value, int position)
{
  int index; // index to the digit being printed, 0 is the leftmost digit
  String valStr = String(value);

  // display each digit in sequence
  for(index = 0; index < 5; index++) // display up to five digits
  {
    char c = valStr.charAt(index);
    if(c == 0)  // check for null (not the same as '0')
      return; // the end of string character is a null
    c = c - 48; // convert ascii value to a numeric value (see Chapter 2)
    showDigit(c, position + index);
  }
}
