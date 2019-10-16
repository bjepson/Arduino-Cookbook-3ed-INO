/*
 * SetTimeSerial sketch
 * Set the time from the serial port. Simplified version of TimeSerial example
 * from the Time library.
 *
 * Set the time by sending the letter T followed by ten digits indicating
 * number of seconds since January 1, 1970, for example T1569888000 would
 * represent 12am on October 1, 2019.
 */

#include <TimeLib.h>

#define TIME_HEADER  'T'   // Header tag for serial time sync message

void setup()  {
  Serial.begin(9600);
  Serial.println("Waiting for time sync message");
}

void loop(){
  if(Serial.available())
  {
    processSyncMessage();
  }
  if(timeStatus() != timeNotSet)
  {
    // Display the time and date
    digitalClockDisplay();
  }
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

// Parse the time message
void processSyncMessage() {

  time_t pctime = 0;

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     setTime(pctime); // Set clock to the time received on serial port
  }

}
