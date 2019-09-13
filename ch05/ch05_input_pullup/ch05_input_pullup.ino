/*
  Input pullup sketch
  a switch connected to pin 2 lights the built-in LED
*/

const int inputPin = 2; // input pin for the switch

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(inputPin, INPUT_PULLUP); // use internal pull-up on inputPin
}

void loop(){
  int val = digitalRead(inputPin);  // read input value
  if (val == HIGH)                  // check if the input is HIGH
  {
    digitalWrite(LED_BUILTIN, LOW);  // turn LED off
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn LED on
  }
}
