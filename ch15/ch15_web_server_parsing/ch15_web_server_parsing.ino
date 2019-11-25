/*
 * WebServerParsing
 * Respond to requests in the URL to change digital and analog output ports
 * show the number of ports changed and the value of the analog input pins.
 * for example:
 *   sending http://192.168.1.177/?pinD2=1 turns digital pin 2 on
 *   sending http://192.168.1.177/?pinD2=0 turns pin 2 off. 
 * This sketch demonstrates text parsing using Arduino Stream class.
 */

#include <SPI.h>        
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,1,177 }; // set to valid address on your network

EthernetServer server(80);

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("ready");
}

void loop()
{
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        // counters to show the number of pin change requests
        int digitalRequests = 0;  
        int analogRequests = 0;
        if( client.find("GET /") ) {  // search for 'GET'
          // find tokens starting with "pin" and stop on the first blank line
          // search to the end of line for 'pin'
          while(client.findUntil("pin", "\n\r")){  
            char type = client.read(); // D or A
            // the next ascii integer value in the stream is the pin
            int pin = client.parseInt(); 
            int val = client.parseInt(); // the integer after that is the value
            if( type == 'D') {
              Serial.print("Digital pin ");
              pinMode(pin, OUTPUT);
              digitalWrite(pin, val);
              digitalRequests++;
            }
            else if( type == 'A'){
              Serial.print("Analog pin ");
              analogWrite(pin, val);
              analogRequests++;
            }
            else {
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
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}
