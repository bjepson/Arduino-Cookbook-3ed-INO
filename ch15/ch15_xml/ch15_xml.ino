/*
 * Simple Weather Client
 * gets xml data from http://openweathermap.org/
 * reads temperature from field:  <temperature value="44.89"
 * writes temperature to analog output port.
*/

// Uncomment only one of the following
#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

char serverName[] = "api.openweathermap.org";
String request = "GET /data/2.5/weather?q=London,UK&units=imperial&mode=xml&APPID=";
String APIkey = "YOUR_KEY_HERE"; // see text

void setup()
{
  Serial.begin(9600);
  if (!configureNetwork()) // Start the network
  {
    Serial.println("Failed to configure the network");
    while (1); // halt
  }
}

void loop()
{
  if (client.connect(serverName, 80) > 0)
  {
    Serial.println("Connected");
    // get weather
    client.println(request + APIkey + " HTTP/1.0");
    client.print("Host: "); client.println(serverName);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println(" connection failed");
  }
  
  if (client.connected())
  {
    if (client.find("<temperature value=") )
    {
      int temperature = client.parseInt();
      Serial.print("Temperature: "); Serial.println(temperature);
    }
    else
      Serial.print("Could not find temperature field");

    if (client.find("<humidity value="))
    {
      int humidity = client.parseInt();
      Serial.print("Humidity: "); Serial.println(humidity);
    }
    else
      Serial.print("Could not find humidity field");
  }
  else 
  {
    Serial.println("Disconnected");
  }
  
  client.stop();
  client.flush();
  delay(60000); // wait a minute before next update
}
