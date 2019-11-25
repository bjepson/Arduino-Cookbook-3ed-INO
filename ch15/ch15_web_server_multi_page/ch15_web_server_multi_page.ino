/*
 * WebServerMultiPage sketch
 * Respond to requests in the URL to view digital and analog output ports
 * http://IP_ADDRESS/analog/   displays analog pin data
 * http://IP_ADDRESS/digital/  displays digital pin data
 */

// Uncomment only one of the following
//#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

const int MAX_PAGE_NAME_LEN = 8;  // max characters in a page name 
char buffer[MAX_PAGE_NAME_LEN+1];  // page name + terminating null

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
    Serial.print(getIP()); Serial.println("/analog/");
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
        if( client.find("GET ") ) 
        {
          // look for the page name
          memset(buffer,0, sizeof(buffer)); // clear the buffer
          if(client.find( "/"))    
            if(client.readBytesUntil('/', buffer, MAX_PAGE_NAME_LEN ))  
            {  
              if(strcmp(buffer, "analog") == 0)
                showAnalog();
              else if(strcmp(buffer, "digital") == 0)
                showDigital();
              else
                unknownPage(buffer);
            }       
        }
        Serial.println();
        break; // Exit the while() loop
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}

void showAnalog()
{
  Serial.println("analog");
  sendHeader();
  client.println("<h1>Analog Pins</h1>");
  // output the value of each analog input pin
  for (int i = 0; i < 6; i++) 
  {
    client.print("analog pin ");
    client.print(i);
    client.print(" = ");
    client.print(analogRead(i));
    client.println("<br />");
  }
}

void showDigital()
{
  Serial.println("digital");
  sendHeader();
  client.println("<h1>Digital Pins</h1>");
  // show the value of each digital pin
  for (int i = 2; i < 8; i++) 
  {
    pinMode(i, INPUT_PULLUP);
    client.print("digital pin ");
    client.print(i);
    client.print(" is ");
    if(digitalRead(i) == LOW)
      client.print("HIGH");
    else
      client.print("LOW");
    client.println("<br />");
  }
  client.println("</body></html>");
}

void unknownPage(char *page)
{
  sendHeader();
  client.println("<h1>Unknown Page</h1>");
  client.print(page);
  client.println("<br />");
  client.println("Recognized pages are:<br />");
  client.println("/analog/<br />");
  client.println("/digital/<br />");
  client.println("</body></html>");
}

void sendHeader()
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<html><head><title>Web server multi-page Example</title>");
  client.println("<body>");
}
