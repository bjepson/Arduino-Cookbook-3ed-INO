/*
 * Incoming request sketch
 * Respond to requests in the URL to change digital and analog output ports
 * show the number of ports changed and the value of the analog input pins.
 * for example:
 *   sending http://IP_ADDRESS/?pinD2=1 turns digital pin 2 on
 *   sending http://IP_ADDRESS/?pinD2=0 turns pin 2 off. 
 * This sketch demonstrates text parsing using Arduino Stream class.
 */

// Uncomment only one of the following
//#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

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
    Serial.print("Try http://");
    Serial.print(getIP()); Serial.println("?pinD2=1");
    nextMsgTime = millis() + MSG_DELAY;
  }

  maintain(); // Maintain the DHCP lease manually if needed

  client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {
      if (client.available()) 
      {
        // counters to show the number of pin change requests
        int digitalRequests = 0;  
        int analogRequests = 0;
        if( client.find("GET /") ) // search for 'GET'
        {  
          // find tokens starting with "pin" and stop on the first blank line
          // search to the end of line for 'pin'
          while(client.findUntil("pin", "\n\r"))
          {  
            char type = client.read(); // D or A
            // the next ascii integer value in the stream is the pin
            int pin = client.parseInt(); 
            int val = client.parseInt(); // the integer after that is the value
            if( type == 'D') 
            {
              Serial.print("Digital pin ");
              pinMode(pin, OUTPUT);
              digitalWrite(pin, val);
              digitalRequests++;
            }
            else if( type == 'A')
            {
              Serial.print("Analog pin ");
              analogWrite(pin, val);
              analogRequests++;
            }
            else 
            {
              Serial.print("Unexpected type ");
              Serial.print(type);
            }
            Serial.print(pin);
            Serial.print("=");
            Serial.println(val);
          }
        }
        Serial.println();

        // the findUntil has detected the blank line (a lf followed by cr)
        // so the http request has ended and we can send a reply
        // send a standard http response header
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();

        // output the number of pins handled by the request
        client.print(digitalRequests);
        client.print(" digital pin(s) written");
        client.println("<br />");
        client.print(analogRequests);
        client.print(" analog pin(s) written");
        client.println("<br />");
        client.println("<br />");

        // output the value of each analog input pin
        for (int i = 0; i < 6; i++) {
          client.print("analog input ");
          client.print(i);
          client.print(" is ");
          client.print(analogRead(i));
          client.println("<br />");
        }
        break; // Exit the while() loop
      }
    }
    // give the web browser time to receive the data
    delay(100);
    client.stop();
  }
}
