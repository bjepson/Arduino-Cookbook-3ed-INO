/*
 * tmp36 sketch
 * prints the temperature to the Serial Monitor 
 * and turns on the LED when a threshold is reached
 */

const int inPin  = A0; // analog pin
const int ledPin = LED_BUILTIN;
const int threshold = 80; // Turn on the LED over 80F

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(inPin);

  float millivolts = (value / 1024.0) * 3300; // Use 3300 instead of 5000 for 3.3V boards
  float celsius = (millivolts - 500) / 10;    // 10mV per degree Celsius with a 500mv offset
  float fahrenheit = (celsius * 9)/ 5 + 32;

  Serial.print("C:");
  Serial.print(celsius);
  Serial.print(",");
  Serial.print("F:");
  Serial.println( fahrenheit );  //  converts to fahrenheit

  if (fahrenheit > threshold){    // is the temperature over the threshold?
    digitalWrite(ledPin, HIGH);  // if it is turn on the LED
  } else {
    digitalWrite(ledPin, LOW);   // if it isn't turn the LED off
  }
  delay(1000); // wait for one second

}
