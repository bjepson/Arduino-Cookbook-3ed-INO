/*
   Pushbutton sketch
   a switch connected to pin 2 lights the LED on pin 13
*/

const int inputPin = 2;           // choose the input pin (for a pushbutton)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // declare LED as output
  pinMode(inputPin, INPUT);       // declare pushbutton as input
}

void loop()
{
  // turn LED ON if input pin is HIGH, else turn OFF
  digitalWrite(LED_BUILTIN, digitalRead(inputPin));  
}
