/*
 * myDelay example sketch to blink an LED for a set amount of time
 */
const int ledPin =  LED_BUILTIN; // the number of the LED pin

int ledState = LOW;               // ledState used to set the LED
unsigned long previousMillis = 0; // will store last time LED was updated

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (myDelay(blink, 250))
  {
    Serial.println(millis() / 1000.0); // print elapsed time in seconds
  }
}

/*
 * Perform the specified function, return true if it was performed
 */
bool myDelay(void (*func)(void), long interval)
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    func(); // invoke the function
    return true;
  }
  return false;
}

void blink()
{
  // if the LED is off turn it on and vice versa:
  if (ledState == LOW)
  {
    ledState = HIGH;
  }
  else
  {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
}
