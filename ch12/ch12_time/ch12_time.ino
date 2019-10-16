/*
 * Time sketch
 */

#include <TimeLib.h>

void setup()
{
  Serial.begin(9600);
  setTime(12,0,0,1,1,2020); // set time to noon Jan 1 2020
}

void loop()
{
  digitalClockDisplay();
  delay(1000);
}

// Pad digits with a leading 0
String padDigits(int digit)
{
  String str = String("0") + digit; // Put a zero in front of the digit
  return str.substring(str.length() - 2); // Remove all but the last two characters
}

void digitalClockDisplay(){
  String timestr = String(hour()) + ":" + padDigits(minute()) + ":" + padDigits(second());
  Serial.println(timestr);
  
  String datestr = String(year()) + "-" + padDigits(month()) + "-" + padDigits(day()); 
  Serial.println(datestr);
}
