/*
 * Client-agnostic web data extraction sketch
 * A sketch that can work with ESP8266, WiFiNINA, and Ethernet boards
 */

//#include "USE_NINA.h"
//#include "USE_Ethernet.h"
//#include "USE_ESP8266.h"

#include <TimeLib.h>

void setup()
{
  Serial.begin(9600);
  if (!configureNetwork()) // Start the network
  {
    Serial.println("Failed to configure the network");
    while (1); // halt
  }

  if(client.connect("api.open-notify.org", 80) > 0) {
    Serial.println("Connected");
    client.println("GET /iss-now.json HTTP/1.0"); // the HTTP request
    client.println("Host: api.open-notify.org");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
    while (1); // halt
  }
}

char timestampMarker[] = "\"timestamp\":";
char posMarker[] = "\"iss_position\":";
void loop()
{
  if (client.available()) {
    if (client.find(timestampMarker)) // Start of timestamp
    {
      unsigned long timestamp = client.parseInt();
      setTime(timestamp); // Set clock to the time of the response
      digitalClockDisplay();
    }

    if (client.find(posMarker)) // Start of position data
    {
      while (client.find("\"")) // Labels start with a "
      {
        String id = client.readStringUntil('"'); // Read the label
        float val = client.parseFloat(); // Read the value
        client.find("\""); // Consume the trailing " after the float

        Serial.print(id + ": "); Serial.println(val, 4); 
      }
    }
  }
  if (!client.connected()) 
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    while(1)
      delay(0); // halt; ESP8266 does not like ∞ loop without a delay
  }
}

String padDigits(int digit)
{
  String str = String("0") + digit; // Put a zero in front of the digit
  return str.substring(str.length() - 2); // Remove all but the last two characters
}

void digitalClockDisplay()
{
  String datestr = String(year()) + "-" + padDigits(month()) + 
                   "-" + padDigits(day()); 
  String timestr = String(hour()) + ":" + padDigits(minute()) +
                   ":" + padDigits(second());
  Serial.println(datestr + " " + timestr);
}
