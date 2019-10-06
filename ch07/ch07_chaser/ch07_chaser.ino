/* Chaser
 */

const int NbrLEDs = 6;
const int ledPins[] = {2, 3, 4, 5, 6, 7};
const int wait_time = 30;

// Swap values of the following two #defines if cathodes are connected to Gnd
#define LED_ON  HIGH
#define LED_OFF LOW

void setup() {
  for (int led = 0; led < NbrLEDs; led++)
  {
    pinMode(ledPins[led], OUTPUT);
  }
}

void loop() {
  for (int led = 0; led < NbrLEDs - 1; led++)
  {
    digitalWrite(ledPins[led], LED_ON);
    delay(wait_time);
    digitalWrite(ledPins[led + 1], LED_ON);
    delay(wait_time);
    digitalWrite(ledPins[led], LED_OFF);
    delay(wait_time * 2);
  }
  for (int led = NbrLEDs - 1; led > 0; led--) {
    digitalWrite(ledPins[led], LED_ON);
    delay(wait_time);
    digitalWrite(ledPins[led - 1], LED_ON);
    delay(wait_time);
    digitalWrite(ledPins[led], LED_OFF);
    delay(wait_time * 2);
  }
}
