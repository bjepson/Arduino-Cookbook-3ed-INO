/*
 *  LED bar graph - decay version
 */

const int ledPins[] = {2, 3, 4, 5, 6, 7};
const int NbrLEDs = sizeof(ledPins) / sizeof(ledPins[0]);
const int analogInPin = A0; // Analog input pin connected to variable resistor
const int decay = 10;       // increasing this reduces decay rate of storedValue

// Swap values of the following two #defines if cathodes are connected to Gnd
#define LED_ON  LOW
#define LED_OFF HIGH

// the stored (decaying) sensor value
int storedValue = 0;

void setup() {
  for (int led = 0; led < NbrLEDs; led++)
  {
    pinMode(ledPins[led], OUTPUT);  // make all the LED pins outputs
  }
}

void loop() {
  int sensorValue = analogRead(analogInPin);             // read the analog in value
  storedValue = max(sensorValue, storedValue);       // use sensor value if higher
  int ledLevel = map(storedValue, 10, 1023, 0, NbrLEDs); // map to number of LEDs

  for (int led = 0; led < NbrLEDs; led++)
  {
    if (led < ledLevel ) {
      digitalWrite(ledPins[led], LED_ON);  // turn on pins less than the level
    }
    else {
      digitalWrite(ledPins[led], LED_OFF);   // turn off pins higher than the level
    }
  }
  storedValue = storedValue - decay;     // decay the value
  delay(10);                             // wait 10 ms before next loop
}
