/*
 * myDelay example sketch to blink an LED for a set amount of time
 */
const int ledPin =  LED_BUILTIN; // the number of the LED pin

int ledState = LOW;              // ledState used to set the LED
long previousMillis = 0;         // will store last time LED was updated

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(millis() / 1000); // print elapsed time in seconds
  // wait four seconds (but at the same time, quickly blink an LED)
  myDelay(4000);                 
}

// duration is delay time in milliseconds
void myDelay(unsigned long duration)
{
  unsigned long start = millis();
  while (millis() <= start + duration)
  {
    blink(100);  // blink the LED inside the while loop
  }
}

// interval is the time that the LED is on and off
void blink(long interval)
{
  if (millis() >= previousMillis + interval)
  {
    // save the last time you blinked the LED
    previousMillis = millis();
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
}
