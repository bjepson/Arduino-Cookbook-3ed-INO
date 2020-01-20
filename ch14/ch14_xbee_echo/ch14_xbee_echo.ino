/*
 * XBee Echo sketch
 * Reply with whatever you receive over the serial port
 */

// Uncomment only one of the following
//#define MYSERIAL Serial // Uno, Nano, and other AVR boards
#define MYSERIAL Serial1 // Nano Every, Uno WiFi R2, Leonardo and ARM boards

void setup()
{
  MYSERIAL.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  while (MYSERIAL.available() ) {
    MYSERIAL.write(MYSERIAL.read()); // reply with whatever you receive
    digitalWrite(LED_BUILTIN, HIGH); // flash LED to show activity
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
  }
}
