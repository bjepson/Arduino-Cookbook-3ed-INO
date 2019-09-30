/* GPS sketch
 * Indicate which hemisphere your GPS is in with the built-in LED.
 */

#include "TinyGPS++.h"

// Change this to the serial port your GPS uses (Serial, Serial1, etc.)
#define GPS_SERIAL Serial

TinyGPSPlus gps; // create a TinyGPS++ object

#define HEMISPHERE_PIN LED_BUILTIN

void setup()
{
  GPS_SERIAL.begin(9600); // GPS devices frequently operate at 9600 baud
  pinMode(HEMISPHERE_PIN, OUTPUT);
  digitalWrite(HEMISPHERE_PIN, LOW); // turn off LED to start
}

void loop()
{
  while (GPS_SERIAL.available())
  {
    // encode() each byte; if encode() returns "true",
    // check for new position.
    if (gps.encode(GPS_SERIAL.read()))
    {
      if (gps.location.isValid()) 
      {
        if (gps.location.lat() < 0) // Southern Hemisphere?
          blink(HEMISPHERE_PIN, 1);
        else
          blink(HEMISPHERE_PIN, 2);
      } else // panic
        blink(HEMISPHERE_PIN, 5);
      delay(5000); // Wait 5 seconds
    }
  }
}

void blink(int pin, int count)
{
  for (int i = 0; i < count; i++)
  {
    digitalWrite(pin, HIGH);
    delay(250);
    digitalWrite(pin, LOW);
    delay(250);
  }
}
