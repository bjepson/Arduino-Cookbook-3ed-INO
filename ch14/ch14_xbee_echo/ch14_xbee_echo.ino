/*
 * XBee Echo sketch
 * Reply with whatever you receive over the serial port
 */

#define MYSERIAL Serial // Uno, Nano, and other ATmega328 boards
//#define MYSERIAL Serial1 // Uncomment for Leonardo and most ARM-based boards

void setup()
{
    MYSERIAL.begin(9600);
}

void loop()
{
  while (MYSERIAL.available() ) {
    MYSERIAL.write(MYSERIAL.read()); // reply with whatever you receive
  }
}
