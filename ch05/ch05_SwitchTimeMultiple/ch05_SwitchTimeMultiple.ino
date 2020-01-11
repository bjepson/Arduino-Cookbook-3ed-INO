/*
 SwitchTimeMultiple sketch
 Prints how long more than one switch has been pressed
 */

const int switchAPin = 2;  // the pin for switch A
const int switchBPin = 3;  // the pin for switch B

void setup()
{
  pinMode(switchAPin, INPUT_PULLUP);
  pinMode(switchBPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  unsigned long timeA;
  unsigned long timeB;

  timeA = switchATime();
  timeB = switchBTime();

  if (timeA > 0 || timeB > 0)
  {
    Serial.print("switch A time=");
    Serial.print(timeA);

    Serial.print(", switch B time=");
    Serial.println(timeB);
  }
}

unsigned long switchTime(int pin, bool &state, unsigned long  &startTime)
{
  if(digitalRead(pin) != state) // check to see if the switch has changed state
  {
    state = ! state;       // yes,  invert the state
    startTime = millis();  // store the time
  }
  if(state == LOW)
  {
    return millis() - startTime;   // return the time in milliseconds
  }
  else
  {
    return 0; // return 0 if the switch is not pushed (in the HIGH state);
  }
}

long switchATime()
{
  // these variables are static - see text for an explanation
  // the time the switch state change was first detected
  static unsigned long startTime = 0;   
  static bool state;  // the current state of the switch
  return switchTime(switchAPin, state, startTime);
}

long switchBTime()
{
  // these variables are static - see text for an explanation
  // the time the switch state change was first detected
  static unsigned long startTime = 0;   
  static bool state;  // the current state of the switch
  return switchTime(switchBPin, state, startTime);
}
