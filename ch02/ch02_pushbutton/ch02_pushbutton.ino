/*
   Pushbutton sketch
   a switch connected to digital pin 2 lights the LED on pin 13
*/

const int inputPin = 2;           // choose the input pin (for a pushbutton)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // declare LED pin as output
  pinMode(inputPin, INPUT_PULLUP);  // declare pushbutton pin as input
}

void loop(){
  int val = digitalRead(inputPin);  // read input value
  if (val == LOW)                   // check if the input is LOW
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn LED on if switch is pressed
  }
}
