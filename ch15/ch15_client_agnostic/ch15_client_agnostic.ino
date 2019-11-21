/*
 * Client-agnostic sketch
 * A sketch that can work with ESP8266, WiFiNINA, and Ethernet boards
 */

#include "USE_ESP.h"

void setup()
{
  Serial.begin(9600);
  if (!configureNetwork()) { // Start the network
    Serial.println("Failed to configure the network");
    while (true); // halt
  }

  if(client.connect("archive.org", 80) > 0) {
    Serial.println(" connected");
    client.println("GET /wayback/available?url=arduino.org HTTP/1.1"); // the HTTP request
    client.println("Host: archive.org");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }

}

char timestampMarker[] = "\"timestamp\": \"";
void loop()
{
  if (client.available()) {
    if (client.find(timestampMarker)) // Start of timestamp
    {
      String timestamp = client.readStringUntil('"'); // End of timestamp
      Serial.print("Latest snapshot: ");
      String year  = timestamp.substring(0, 4);
      String month = timestamp.substring(4, 6);
      String day   = timestamp.substring(6, 8);
      String hour  = timestamp.substring(8, 10);
      String min   = timestamp.substring(10, 12);
      Serial.print(year + "-" + month + "-" + day + "@");
      Serial.print(hour + ":" + min);
    }
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    while(true); // halt
  }
}
