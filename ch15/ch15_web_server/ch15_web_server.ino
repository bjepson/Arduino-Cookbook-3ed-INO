/*
 * WiFi Web Server sketch
 */

// Uncomment only one of the following
//#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
#include "USE_ESP8266.h"  // ESP8266 boards

void setup() {
  Serial.begin(9600);
  
  if (!configureNetwork()) // Start the network
  {
    Serial.println("Failed to configure the network");
    while(1)
      delay(0); // halt; ESP8266 does not like ∞ loop without a delay
  }
  server.begin();
}

#define MSG_DELAY 10000
void loop() {
  static unsigned long nextMsgTime = 0;
  if (millis() > nextMsgTime)
  {
    Serial.print("Visit me at http://");
    Serial.println(getIP());
    nextMsgTime = millis() + MSG_DELAY;
  }

  maintain(); // Maintain the DHCP lease manually if needed

  client = server.available(); // Listen for connections
  if (client) {
    Serial.println("New client connection");
    
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.write(c);
        // If you've reached the end of a blank line and found another \n,
        // then you've reached the end of the headers.
        if (c == '\n' && currentLineIsBlank) 
        {
          // Send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); // Close connection at end of response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println(); // End of headers

          client.println("<!DOCTYPE HTML>");
          client.println("<HTML>");
          
          // Display the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) 
          {
            int sensorReading = analogRead(analogChannel);
            client.print("A");   client.print(analogChannel);
            client.print(" = "); client.print(sensorReading);
            client.println("<BR />");
          }
          client.println("</HTML>");
          break; // Break out of the while loop
        }
        if (c == '\n') 
        {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') 
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // Give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("Client disonnected");
  }
}
