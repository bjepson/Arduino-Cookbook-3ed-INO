/*
 * WebServerPost sketch
 * Turns pin 8 on and off using HTML form
 */

// Uncomment only one of the following
//#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

const int MAX_PAGE_NAME_LEN = 8;  // max characters in a page name 
char buffer[MAX_PAGE_NAME_LEN+1];  // page name + terminating null


void setup() 
{
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
    Serial.println(getIP());
    nextMsgTime = millis() + MSG_DELAY;
  }

  maintain(); // Maintain the DHCP lease manually if needed

  client = server.available();
  if (client) 
  {
    int type = 0;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        // GET, POST, or HEAD
        memset(buffer,0, sizeof(buffer)); // clear the buffer
        //if(client.find("/"))
        //{
          if(client.readBytesUntil('/', buffer,sizeof(buffer)))
          { 
            Serial.println(buffer);
            if(strcmp(buffer,"POST ") == 0)
            {
              client.find("\n\r"); // skip to the body

              // find string starting with "pin", stop on first blank line
              // the POST parameters expected in the form pinDx=Y
              // where x is the pin number and Y is 0 for LOW and 1 for HIGH
              while(client.findUntil("pinD", "\n\r"))
              {
                int pin = client.parseInt();       // the pin number
                int val = client.parseInt();       // 0 or 1
                pinMode(pin, OUTPUT);
                digitalWrite(pin, val);
              }
            }
            else // probably a GET
            { 
              if (client.find("favicon.ico")) // Send 404 for favicons
                sendHeader("404 Not Found", "Not found");
            }
            sendHeader("200 OK", "Post example");

            //create HTML button to turn off pin 8
            client.println("<h2>Click buttons to turn pin 8 on or off</h2>");
            client.print(
            "<form action='/' method='POST'><p><input type='hidden' name='pinD8'");
            client.println(" value='0'><input type='submit' value='Off'/></form>");

            //create HTML button to turn on pin 8
            client.print(
            "<form action='/' method='POST'><p><input type='hidden' name='pinD8'");
            client.print(" value='1'><input type='submit' value='On'/></form>");
            client.println("</body></html>");
            client.stop();
          }
        //}
        break; // exit the while loop
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}
void sendHeader(char *code, char *title)
{
  // send a standard http response header
  client.print("HTTP/1.1 "); client.println(code);
  client.println("Content-Type: text/html");
  client.println();
  client.print("<html><head><title>");
  client.print(title);
  client.println("</title><body>");
}
