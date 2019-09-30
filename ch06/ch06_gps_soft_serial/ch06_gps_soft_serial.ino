/* GPS sketch with logging
 */

#include "TinyGPS++.h"

// Delete the next fout lines if your board has a separate hardware serial port
#include "SoftwareSerial.h"
#define GPS_RX_PIN 2
#define GPS_TX_PIN 3
SoftwareSerial softserial(GPS_RX_PIN, GPS_TX_PIN); // create soft serial object

// If your board has a separate hardware serial port, change "softserial" to that port
#define GPS_SERIAL softserial

TinyGPSPlus gps; // create a TinyGPSPlus object

void setup()
{
  Serial.begin(9600); // for debugging
  GPS_SERIAL.begin(9600); // Use Soft Serial object to talk to GPS
}
void loop()
{
  while (GPS_SERIAL.available())
  {
    int c = GPS_SERIAL.read();
    Serial.write(c); // display NMEA data for debug

    // Send each byte to encode()
    // Check for new position if encode() returns "True"
    if (gps.encode(c))
    {
      Serial.println();
      float lat = gps.location.lat();
      float lng = gps.location.lng();
      unsigned long fix_age = gps.date.age();
    
      if (!gps.location.isValid())
        Serial.println("Invalid fix");
      else if (fix_age > 2000)
        Serial.println("Stale fix");
      else
        Serial.println("Valid fix");
      
      Serial.print("Lat: "); 
      Serial.print(lat);
      Serial.print(" Lon: "); 
      Serial.println(lng);
    }
  }
}
