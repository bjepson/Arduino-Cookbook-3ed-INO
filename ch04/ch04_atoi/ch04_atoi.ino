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

const int maxChars = 5;    // an int string contains up to 5 digits and
                           // is terminated by a 0 to indicate end of string
char strValue[maxChars+1]; // must be big enough for digits and terminating null
int idx = 0;               // the index into the array storing the received digits

void loop()
{
  if( Serial.available())
  {
    char ch = (char) Serial.read();
    if( idx < maxChars && isDigit(ch) ){
      strValue[idx++] = ch; // add the ASCII character to the string;
    }
    else
    {
      // here when buffer full or on the first non digit
      strValue[idx] = 0;           // terminate the string with a 0
      blinkDelay = atoi(strValue); // use atoi to convert the string to an int
      Serial.println(blinkDelay);
      idx = 0;
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
