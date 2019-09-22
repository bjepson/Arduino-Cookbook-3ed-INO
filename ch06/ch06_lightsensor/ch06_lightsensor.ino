/*
 * Light sensor sketch
 * 
 * Varies the blink rate based on the measured brightness
 */
const int ledPin = LED_BUILTIN; // Built-in LED
const int sensorPin = 0;        // connect sensor to analog input 0

void setup()
{
  pinMode(ledPin, OUTPUT);  // enable output on the led pin
  Serial.begin(9600);
}

void loop()
{
  int rate = analogRead(sensorPin);    // read the analog input
  Serial.println(rate);
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(rate);                  // wait duration dependent on light level
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(rate);
}
