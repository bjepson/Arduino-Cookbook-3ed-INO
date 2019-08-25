/*
 * StringToNumber
 * Creates a number from a string
 */

int   blinkDelay;     // blink rate determined by this variable

void setup()
{
 Serial.begin(9600); 
 pinMode(LED_BUILTIN, OUTPUT); // enable LED pin as output
 Serial.setTimeout(1000 * 3); // wait up to 3 seconds

}

void loop()
{
  if( Serial.available())
  {
    int newValue = Serial.parseInt();
    if (newValue != 0) {
        blinkDelay = newValue;
        Serial.print("New delay: ");
        Serial.println(blinkDelay);
    }
  }
  blink();
}

void blink()
{
   digitalWrite(LED_BUILTIN, HIGH);
   delay(blinkDelay/2);  // wait for half the blink period 
   digitalWrite(LED_BUILTIN, LOW);
   delay(blinkDelay/2);  // wait for the other half 
}
