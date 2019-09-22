/* 
 * tilt sketch
 * 
 * a tilt sensor attached to pin 2 lights one of
 * the LEDs connected to pins 11 and 12 depending
 * on which way the sensor is tilted
 */

const int tiltSensorPin = 2;  // pin the tilt sensor is connected to
const int firstLEDPin  = 11;  // pin for one LED
const int secondLEDPin = 12;  // pin for the other

void setup()
{
  pinMode (tiltSensorPin, INPUT_PULLUP); // Tilt sensor connected to this pin

  pinMode (firstLEDPin, OUTPUT);   // first output LED
  pinMode (secondLEDPin, OUTPUT);  // and the second
}

void loop()
{
  if (digitalRead(tiltSensorPin) == LOW){ // The switch is on (upright)
    digitalWrite(firstLEDPin, HIGH);      // Turn on the first LED
    digitalWrite(secondLEDPin, LOW);      // and turn off the second.
  }
  else{                                   // The switch is off (tilted)
    digitalWrite(firstLEDPin, LOW);       // Turn the first LED off
    digitalWrite(secondLEDPin, HIGH);     // and turn on the second.
  }
}
