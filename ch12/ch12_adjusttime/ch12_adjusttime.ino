/*
   AdjustClockTime sketch
   buttons on pins 2 and 3 adjust the time
 */

#include <TimeLib.h>

const int  btnForward = 2;  // button to move time forward
const int  btnBack = 3;     // button to move time back

unsigned long  prevtime;   // when the clock was last displayed

void setup()
{
  pinMode(btnForward, INPUT_PULLUP);  // enable internal pull-up resistors
  pinMode(btnBack, INPUT_PULLUP);
  setTime(12,0,0,1,1,2020); // start with the time set to noon Jan 1 2020
  Serial.begin(9600);
}

void loop()
{
  prevtime = now();   // note the time
  while( prevtime == now() )    // stay in this loop till the second changes
  {
    // check if the set button pressed while waiting for second to roll over
    if(checkSetTime())
      prevtime = now(); // time changed so reset start time
  }
  digitalClockDisplay();
}
    
// functions checks to see if the time should be adjusted
// returns true if time was changed
bool checkSetTime()
{
  int step;   // the number of seconds to move (backwards if negative) 
  bool isTimeAdjusted = false;  // set to true if the time is adjusted
  step = 1;   // ready to step forwards

  while(digitalRead(btnForward)== LOW)
  {
     adjustTime(step);
     isTimeAdjusted = true; // to tell the user that the time has changed
     step = step + 1; // next step will be bigger
     digitalClockDisplay(); // update clock   
     delay(100); 
  }
  step = -1;   // negative numbers step backwards
  while(digitalRead(btnBack)== LOW)
  {
     adjustTime(step);
     isTimeAdjusted = true; // to tell the user that the time has changed
     step = step - 1; // next step will be a bigger negative number
     digitalClockDisplay(); // update clock   
     delay(100); 
  }
  return isTimeAdjusted;  // tell the user if the time was adjusted
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
