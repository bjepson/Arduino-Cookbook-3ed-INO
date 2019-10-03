/*
 * LEDs sketch
 * Blink three LEDs each connected to a different digital pin
 */

const int firstLedPin  = 3; // choose the pin for each of the LEDs
const int secondLedPin = 5;
const int thirdLedPin  = 6;

void setup()
{
  pinMode(firstLedPin, OUTPUT);  // declare LED pins as output
  pinMode(secondLedPin, OUTPUT); // declare LED pins as output
  pinMode(thirdLedPin, OUTPUT);  // declare LED pins as output
}

void loop()
{
  // flash each of the LEDs for 1000 milliseconds (1 second)
  blinkLED(firstLedPin,  1000);
  blinkLED(secondLedPin, 1000);
  blinkLED(thirdLedPin,  1000);
}


// blink the LED on the given pin for the duration in milliseconds
void blinkLED(int pin, int duration)
{
  digitalWrite(pin, HIGH);     // turn LED on
  delay(duration);
  digitalWrite(pin, LOW);      // turn LED off
  delay(duration);
}
