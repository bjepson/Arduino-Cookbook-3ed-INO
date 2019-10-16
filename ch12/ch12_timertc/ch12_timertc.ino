/*
 * TimeRTC sketch
 * example code illustrating Time library with real-time clock.
 *
 */

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

void setup()  {
  Serial.begin(9600);
  while(!Serial); // For Leonardo and 32-bit boards
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet)
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
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
  String timestr = String(hour()) + ":" + padDigits(minute()) +
                   ":" + padDigits(second());
  Serial.println(timestr);
  
  String datestr = String(year()) + "-" + padDigits(month()) + 
                   "-" + padDigits(day()); 
  Serial.println(datestr);
}
