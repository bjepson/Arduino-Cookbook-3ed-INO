/*
 * Debounce sketch
 * a switch connected to pin 2 lights the built-in LED
 * debounce logic prevents misreading of the switch state
 */

const int inputPin = 2;        // the number of the input pin
const int debounceDelay = 10;  // iterations to wait until pin is stable
bool last_button_state = LOW;  // Last state of the button
int ledState = LOW;            // On or off (HIGH or LOW)

// debounce returns the state when the switch is stable
bool debounce(int pin)
{
  bool state;
  bool previousState;

  previousState = digitalRead(pin);          // store switch state
  for(int counter=0; counter < debounceDelay; counter++)
  {
      delay(1);                  // wait for 1 millisecond
      state = digitalRead(pin);  // read the pin
      if( state != previousState)
      {
         counter = 0; // reset the counter if the state changes
         previousState = state;  // and save the current state
      }
  }
  // here when the switch state has been stable longer than the debounce period
  return state;
}

void setup()
{
  pinMode(inputPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  bool button_state = debounce(inputPin);

  // If the button state changed and the button was pressed
  if (last_button_state != button_state && button_state == HIGH) {
    // Toggle the LED
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
  last_button_state = button_state;
}
