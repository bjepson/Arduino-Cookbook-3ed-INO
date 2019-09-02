/*
   MultiRX sketch
   Receive data from two software serial ports
*/
#include <SoftwareSerial.h>
const int rxpin1 = 8;
const int txpin1 = 9;
const int rxpin2 = 10;
const int txpin2 = 11;

SoftwareSerial gps(rxpin1, txpin1); // gps device connected to pins 2 and 3
SoftwareSerial xbee(rxpin2, txpin2); // xbee device connected to pins 4 and 5

void setup()
{
  Serial.begin(9600);
  xbee.begin(9600);
  gps.begin(9600);
  xbee.listen(); // Set “xbee” to be the active device
}

void loop()
{
  xbee.listen(); // Set “xbee” to be the active device
  if (xbee.available() > 0) // xbee is active. Any characters available?
  {
    if (xbee.read() == 'y') // if xbee received a 'y' character?
    {
      Serial.println("Got a y!");
      gps.listen(); // now start listening to the gps device

      unsigned long start = millis(); // begin listening to the GPS
      while (start + 100000 > millis())
        // listen for 10 seconds
      {
        if (gps.available() > 0) // now gps device is active
        {
          char c = gps.read();
          Serial.write(c);              // echo it to the serial console
        }
      }
      xbee.listen(); // After 10 seconds, go back to listening to the xbee
    }
  }
}
