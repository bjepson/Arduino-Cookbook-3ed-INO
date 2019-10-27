/*
 * OptoRemote sketch
 * Switches connected to pins 2 and 3 turns a remote device on and off 
 * using optocouplers.
 * The outputs are pulsed for at least half a second when a switch is pressed
 */
const int onSwitchPin  = 2;         // input pin for the On switch
const int offSwitchPin = 3;         // input pin for the Off switch
const int remoteOnPin  = 4;         // output pin to turn the remote on
const int remoteOffPin = 5;         // output pin to turn the remote off
const int PUSHED       = LOW;       // value when button is pressed

void setup() {
  pinMode(remoteOnPin, OUTPUT);
  pinMode(remoteOffPin, OUTPUT);
  pinMode(onSwitchPin, INPUT_PULLUP);  // turn on internal pull-up on the inputPins
  pinMode(offSwitchPin, INPUT_PULLUP);
}

void loop(){
  int val = digitalRead(onSwitchPin);  // read input value
  // if the switch is pushed then switch on if not already on
  if(val == PUSHED)
  {
    pulseRemote(remoteOnPin);
  }

  val = digitalRead(offSwitchPin);  // read input value
  // if the switch is pushed then switch off if not already off
  if(val == PUSHED)
  {
    pulseRemote(remoteOffPin);
  }
}

// turn the optocoupler on for half a second to blip the remote control button
void pulseRemote(int pin)
{
  digitalWrite(pin, HIGH);     // turn the optocoupler on
  delay(500);                  // wait half a second
  digitalWrite(pin, LOW);      // turn the optocoupler off
}
