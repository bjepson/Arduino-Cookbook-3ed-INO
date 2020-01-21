/*
 * Ethernet Web Client sketch
 * Connects to the network without DHCP, using
 * hardcoded IP addresses for device.
 */

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Must be unique
IPAddress ip(192, 168, 1, 177); // Must be a valid address for your network
char serverName[] = "archive.org";

EthernetClient client;

String request = "GET /advancedsearch.php?q=arduino&fl%5B%5D=description"
                 "&rows=1&sort%5B%5D=downloads+desc&output=csv#raw HTTP/1.0";

void setup()
{
  Serial.begin(9600);
  while(!Serial); // for Leonardo and 32-bit boards
  
  Ethernet.begin(mac, ip);
  delay(1000); // give the Ethernet hardware a second to initialize

  Serial.println("Connecting to server...");
  int ret = client.connect(serverName, 80); 
  if (ret == 1) 
  {
    Serial.println("Connected");
    client.println(request);
    client.print("Host: "); client.println(serverName);
    client.println("Connection: close");
    client.println(); // Send the terminating blank line that HTTP requires
  } 
  else 
  {
    Serial.println("Connection failed, error was: ");
    Serial.print(ret, DEC);
  }
}

void loop()
{
  if (client.available()) 
  {
    char c = client.read();
    Serial.print(c);  // echo all data received to the Serial Monitor
  }
  if (!client.connected()) 
  {
    Serial.println();
    Serial.println("Disconnecting.");
    client.stop();
    while(1); // halt
  }
}
