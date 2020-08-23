#include <TimeLib.h>

const int  potPin = A0;    // pot to determine direction and speed
const int  buttonPin = 2;  // button enables time adjustment

unsigned long prevtime;   // when the clock was last displayed

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP); // enable internal pull-up resistors
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
      prevtime = now(); //  time has changed, so reset start time
  }
  digitalClockDisplay();
}

// function checks to see if the time should be adjusted
// return true if time was changed
bool checkSetTime()
{
  int value;  // a value read from the pot
  int step;   // the number of seconds to move (backward if negative)
  bool isTimeAdjusted = false;  // set to true if the time is adjusted

  while(digitalRead(buttonPin)== LOW)
  {
    // here while button is pressed
    value = analogRead(potPin);  // read the pot value
    step = map(value, 0,1023, 10, -10);  // map value to the desired range
    if( step != 0)
    {
      adjustTime(step);
      isTimeAdjusted = true; // to tell the user that the time has changed
      digitalClockDisplay(); // update clock
      delay(100);
    }
  }
  return isTimeAdjusted;
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

  String datestr = String(dayStr(weekday())) + ", " + 
                   String(monthShortStr(month())) + " " + String(year());
  Serial.println(datestr);
}
