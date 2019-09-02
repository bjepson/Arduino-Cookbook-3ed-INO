/*
 * SoftwareSerialInput sketch
 * Read data from a software serial port
 */

#include <SoftwareSerial.h>
const int rxpin = 8;                     // pin used to receive from GPS
const int txpin = 9;                    // pin used to send to GPS
SoftwareSerial serial_gps(rxpin, txpin); // new serial port on pins 2 and 3

void setup()
{
  Serial.begin(9600); // 9600 baud for the built-in serial port
  serial_gps.begin(9600); // initialize the port, most GPS devices 
                          // use 9600 baud
}

void loop()
{
  if (serial_gps.available() > 0) // any character arrived yet?
  {
    char c = serial_gps.read();   // if so, read it from the GPS
    Serial.write(c);              // and echo it to the serial console
  }
}
