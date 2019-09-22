/*
   PIR sketch
   a Passive Infrared motion sensor connected to pin 2
   lights the LED on the built-in LED
*/

const int ledPin = LED_BUILTIN;  // choose the pin for the LED
const int inputPin = 2;          // choose the input pin (for the PIR sensor)

void setup() {
  pinMode(ledPin, OUTPUT);       // declare LED as output
  pinMode(inputPin, INPUT);      // declare pin as input
}

void loop(){
  int val = digitalRead(inputPin);  // read input value
  if (val == HIGH)                  // check if the input is HIGH
  {
    digitalWrite(ledPin, HIGH);     // turn LED on if motion detected
    delay(500);
    digitalWrite(ledPin, LOW);      // turn LED off
  }
}
