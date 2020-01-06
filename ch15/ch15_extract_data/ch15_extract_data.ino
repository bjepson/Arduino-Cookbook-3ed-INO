/*
 * Client-agnostic web data extraction sketch
 * A sketch that can work with ESP8266, WiFiNINA, and Ethernet boards
 */

// Uncomment only one of the following
#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

#include <TimeLib.h>

char server[] = "api.open-notify.org";
void setup()
{
  Serial.begin(9600);
  if (!configureNetwork()) // Start the network
  {
    Serial.println("Failed to configure the network");
    while(1) 
    {
      delay(0); // halt; ESP8266 does not like ∞ loop without a delay
    }
  }

  int ret = client.connect(server, 80); 
  if (ret == 1) 
  {
    Serial.println("Connected");
    client.println("GET /iss-now.json HTTP/1.0"); // the HTTP request
    client.print("Host: "); client.println(server);
    client.println("Connection: close");
    client.println();
  } 
  else 
  {
    Serial.println("Connection failed, error was: ");
    Serial.print(ret, DEC);
    while(1)
    {
      delay(0); // halt; ESP8266 does not like ∞ loop without a delay
    }
  }
}

char timestampMarker[] = "\"timestamp\":";
char posMarker[] = "\"iss_position\":";
void loop()
{
  if (client.available()) {
    if (client.find('"')) // Start of a string identifier
    {
      String id = client.readStringUntil('"');
      if (id.equals("timestamp")) // Start of timestamp
      {
        if (client.find(':')) // A ":" follows each identifier
        {
          unsigned long timestamp = client.parseInt();
          setTime(timestamp); // Set clock to the time of the response
          digitalClockDisplay();          
        }
        else
        {
          Serial.println("Failed to parse timestamp.");
        }
      }

      if (id.equals("iss_position")) // Start of position data
      {
        if (client.find(':')) // A ":" follows each identifier
        {
          // Labels start with a " and position data ends with a }
          while (client.peek() != '}' && client.find('"')) 
          {
            String id = client.readStringUntil('"'); // Read the label
            float val = client.parseFloat(); // Read the value
            client.find('"'); // Consume the trailing " after the float
            Serial.print(id + ": "); Serial.println(val, 4); 
          }      
        }
        else
        {
          Serial.println("Failed to parse position data.");
        }
      }
    }
  }

  if (!client.connected()) 
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    while(1)
    {
      delay(0); // halt; ESP8266 does not like ∞ loop without a delay
    }
  }
}

String padDigits(int digit)
{
  String str = String("0") + digit; // Put a zero in front of the digit
  return str.substring(str.length() - 2); // Remove all but last two characters
}

void digitalClockDisplay()
{
  String datestr = String(year()) + "-" + padDigits(month()) + 
                   "-" + padDigits(day()); 
  String timestr = String(hour()) + ":" + padDigits(minute()) +
                   ":" + padDigits(second());
  Serial.println(datestr + " " + timestr);
}
