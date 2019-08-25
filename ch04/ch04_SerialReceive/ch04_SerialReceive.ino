/*
 * SerialReceive sketch
 * Blink the LED at a rate proportional to the received digit value
*/
int blinkDelay = 0;  // blink delay stored in this variable

void setup()
{
  Serial.begin(9600); // Initialize serial port to send and receive at 9600 baud
  pinMode(LED_BUILTIN, OUTPUT); // set this pin as output
}

void loop()
{
  if (Serial.available()) // Check to see if at least one character is available
  {
    char ch = (char) Serial.read();
    if( isDigit(ch) ) // is this an ascii digit between 0 and 9?
    {
      blinkDelay = (ch - '0');       // ASCII value converted to numeric value
      blinkDelay = blinkDelay * 100; // actual delay is 100ms times received digit
    }
  }
  blink();
}

// blink the LED with the on and off times determined by blinkDelay
void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkDelay); // delay depends on blinkDelay value
  digitalWrite(LED_BUILTIN, LOW);
  delay(blinkDelay);
}
