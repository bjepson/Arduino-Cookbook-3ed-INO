/*
 * Map sketch
 * map the range of analog values from a pot to scale from 0 to 100
 * resulting in an LED blink rate ranging from 0 to 100 milliseconds.
 * and Pot rotation percent is written to the serial port
 */

const int potPin = A0;      // select the input pin for the potentiometer
int ledPin = LED_BUILTIN;  // select the pin for the LED

void setup()
{
  pinMode(ledPin, OUTPUT);     // declare the ledPin as an OUTPUT
  Serial.begin(9600);
}

void loop() {
  int val;     // The value coming from the sensor
  int percent; // The mapped value

  val = analogRead(potPin);        // read the voltage on the pot (val ranges
                                   // from 0 to 1023)
  percent = map(val,0,1023,0,100); // percent will range from 0 to 100.
  digitalWrite(ledPin, HIGH);      // turn the ledPin on
  delay(percent);                  // On time given by percent value
  digitalWrite(ledPin, LOW);       // turn the ledPin off
  delay(100 - percent);            // Off time is 100 minus On time
  Serial.println(percent);         // show the % of pot rotation on Serial Monitor
}
