/*
 * WebServerMultiPageHTML sketch
 * Display analog and digital pin values using HTML formatting
 */

// Uncomment only one of the following
#include "USE_NINA.h"     // WiFiNINA boards
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
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i=0; i < 3; i++)
  {
     digitalWrite(LED_BUILTIN, HIGH);
     delay(500);
     digitalWrite(LED_BUILTIN, LOW);
     delay(500);
  }
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
              if(strcasecmp(buffer, "analog") == 0)
                showAnalog();
              else if(strcasecmp(buffer, "digital") == 0)
                showDigital();
              else
                unknownPage(buffer);
            }
        }
        break;
      }
    }
    // give the web browser time to receive the data
    delay(100);
    client.stop();
  }
}

void showAnalog()
{
  sendHeader("Multi-page: Analog");
  client.println("<h2>Analog Pins</h2>");
  client.println("<table border='1' >");
  for (int i = 0; i < 6; i++) 
  {
    // output the value of each analog input pin
    client.print("<tr><td>analog pin ");
    client.print(i);
    client.print(" </td><td>");
    client.print(analogRead(i));
    client.println("</td></tr>");
  }
  client.println("</table>");
  client.println("</body></html>");
}

void showDigital()
{
  sendHeader("Multi-page: Digital");
  client.println("<h2>Digital Pins</h2>");
  client.println("<table border='1'>");
  for (int i = 2; i < 8; i++) 
  {
    // show the value of digital pins
    pinMode(i, INPUT_PULLUP); // turn on pull-ups
    client.print("<tr><td>digital pin ");
    client.print(i);
    client.print(" </td><td>");
    if(digitalRead(i) == LOW)
      client.print("High");
    else
      client.print("Low");
    client.println("</td></tr>");
  }
  client.println("</table>");
  client.println("</body></html>");
}

void unknownPage(char *page)
{
  sendHeader("Unknown Page");
  client.println("<h1>Unknown Page</h1>");
  client.print(page);
  client.println("<br />");
  client.println("Recognized pages are:<br />");
  client.println("/analog/<br />");
  client.println("/digital/<br />"); 
  client.println("</body></html>");
}

void sendHeader(char *title)
{
  // send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.print("<html><head><title>");
  client.println(title);
  client.println("</title><body>");
}
