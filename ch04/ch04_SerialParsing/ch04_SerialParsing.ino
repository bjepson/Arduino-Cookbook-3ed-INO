/*
* SerialParsing sketch
* Blink the LED at a rate proportional to the received digit value
*/

int blinkDelay = 0;

void setup()
{
  Serial.begin(9600); // Initialize serial port to send and receive at 9600 baud
  pinMode(LED_BUILTIN, OUTPUT); // set this pin as output
}

void loop()
{
  if ( Serial.available()) // Check to see if at least one character is available
  {
    int i = Serial.parseInt();
    if (i != 0) {
        blinkDelay = i;
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
