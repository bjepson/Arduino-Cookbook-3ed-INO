/*
 * Set RTC time sketch
 * Set the RTC from the serial port. Simplified version of TimeSerial example
 * from the Time library.
 *
 * Set the time by sending the letter T followed by ten digits indicating
 * number of seconds since January 1, 1970, for example T1569888000 would
 * represent 12am on October 1, 2019.
 */

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

void setup()  {
  Serial.begin(9600);
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet)
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
}

void loop()
{
  if(Serial.available())
  {
     processSyncMessage();
  }
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

#define TIME_HEADER  'T'   // Header tag for serial time sync message

// Parse the time message
void processSyncMessage() {

  time_t pctime = 0;

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     setTime(pctime); // Set clock to the time received on serial port
     RTC.set(pctime); // Set the RTC too

  }

}
