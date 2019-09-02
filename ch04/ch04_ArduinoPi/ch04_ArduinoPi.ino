/*
 * ArduinoPi sketch
 * Pi control Arduino pins using serial messages
 * format is: Pn=state 
 * where 'P' is header character, n is pin number, state is 0 or 1
 * example: P13=1  turns on pin 13
 */

// Replace Serial with Serial1 on boards with an additional serial port
#define mySerial Serial

void setup()
{
  mySerial.begin(9600); // Initialize serial port to send/receive at 9600 baud
}

void loop()
{
  if (mySerial.available()) // Check whether at least one character is available
  {
    char ch = mySerial.read();
    int pin = -1;
    if( ch == 'P') // is this the beginning of a message to set a pin?
    {
      pin = mySerial.parseInt();   // get the pin number
    }
    else if (ch == 'B') // Message to set LED_BUILTIN
    {
      pin = LED_BUILTIN;
    }
    
    if( pin > 1) { // 0 and 1 are usually serial pins (leave them alone)
      int state = mySerial.parseInt(); // 0 is off, 1 is on
      pinMode(pin, OUTPUT);
      digitalWrite(pin, state);
    }

  }
}
