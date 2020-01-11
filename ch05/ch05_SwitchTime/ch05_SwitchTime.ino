/*
 SwitchTime sketch
 Countdown timer that decrements every tenth of a second
 lights an LED when 0
 Pressing button increments count, holding button down increases
 rate of increment

 */
const int ledPin = LED_BUILTIN;        // the number of the output pin
const int inPin = 2;                   // the number of the input pin

const int debounceTime = 20;           // the time in milliseconds required
                                       // for the switch to be stable
const int fastIncrement = 1000;        // increment faster after this many
                                       // milliseconds
const int veryFastIncrement = 4000;    // and increment even faster after
                                       // this many milliseconds
int count = 0;                         // count decrements every tenth of a
                                       // second until reaches 0
void setup()
{
  pinMode(inPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int duration = switchTime();
  if(duration > veryFastIncrement)
  {
    count = count + 10;
  }
  else if (duration > fastIncrement)
  {
    count = count + 4;    
  }
  else if (duration > debounceTime)
  {
    count = count + 1;
  }
  else
  {
    // switch not pressed so service the timer
    if( count == 0) 
    {
      digitalWrite(ledPin, HIGH);  // turn the LED on if the count is 0
    }
    else
    {
      digitalWrite(ledPin, LOW);   // turn the LED off if the count is not 0
      count = count - 1;           // and decrement the count
    }
  }
  Serial.println(count);
  delay(100);
}

// return the time in milliseconds that the switch has been in pressed (LOW)
long switchTime()
{
  // these variables are static - see Discussion for an explanation
  static unsigned long startTime = 0; // when switch state change was detected
  static bool state;                  // the current state of the switch

  if(digitalRead(inPin) != state) // check to see if the switch has changed state
  {
    state = ! state;       // yes, invert the state
    startTime = millis();  // store the time
  }
  if(state == LOW)
  {
    return millis() - startTime;   // switch pushed, return time in milliseconds
  }
  else
  {
    return 0; // return 0 if the switch is not pushed (in the HIGH state);
  }
}
