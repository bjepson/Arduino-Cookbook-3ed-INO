/*
   Pushbutton sketch
   a switch connected to pin 2 lights the built-in LED
*/

const int inputPin = 2;           // choose the input pin (for a pushbutton)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // declare LED as output
  pinMode(inputPin, INPUT);       // declare pushbutton as input
}

void loop(){
  int val = digitalRead(inputPin);  // read input value
  if (val == HIGH)                  // check if the input is HIGH
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn LED on if switch is pressed
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);  // turn LED off
  }
}
