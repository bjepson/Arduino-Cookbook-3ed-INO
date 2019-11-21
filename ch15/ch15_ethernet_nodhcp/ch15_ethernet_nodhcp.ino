/*
 * Ethernet Web Client sketch
 * Connects to the network without DHCP or DNS, using
 * hardcoded IP addresses for device and remote server
 */

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x3D, 0xCA, 0xFE, 0x0F, 0xBE, 0xEF }; // Must be unique
byte ip[]  = { 192, 168, 137, 177 }; // Must be a valid address for your network
byte server[] = { 207, 241, 224, 2 }; // Archive.org

EthernetClient client;

String request = "GET /advancedsearch.php?q=arduino&fl%5B%5D=description"
                 "&rows=1&sort%5B%5D=downloads+desc&output=csv#raw HTTP/1.1";

void setup()
{
  Serial.begin(9600);
  while(!Serial); // Leonardo and 32-bit boards
  
  Ethernet.begin(mac, ip);
  delay(1000); // give the Ethernet hardware a second to initialize

  Serial.println("Connecting...");
  if (client.connect(server, 80)) 
  {
    Serial.println("Connected");
    client.println(request);
    client.println("Host: archive.org");
    client.println("Connection: close");
    client.println();
  } 
  else 
  {
    Serial.println("Connection failed");
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
