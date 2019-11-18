/*
 * Simple Client to display IP address obtained from DHCP server 
 */

#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;

bool configureNetwork()
{
  bool success = false;
  success = (0 == Ethernet.begin(mac));
  delay(1000); // give the Ethernet module a second to initialize
  return success;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial); // For Leonardo and 32-bit boards
  if (!configureNetwork()) { // Start the network
    Serial.println("Failed to configure the network");
    while (true); // halt
  }
  IPAddress myIPAddress = Ethernet.localIP(); 
  Serial.print("My IP address: ");
  Serial.print(myIPAddress);  
}

void loop()
{
}
