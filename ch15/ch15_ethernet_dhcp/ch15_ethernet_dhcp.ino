/*
 * DHCP sketch
 * Obtain an IP address from the DHCP server and display it
 */

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Must be unique

EthernetClient client;

void setup()
{
  Serial.begin(9600);
  while(!Serial); // for Leonardo and 32-bit boards
  
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    while(1); // halt
  }
  delay(1000); // give the Ethernet hardware a second to initialize

}

#define MAINTAIN_DELAY 750 // Maintain DHCP lease every .75 seconds
void loop()
{
  static unsigned long nextMaintain = millis() + MAINTAIN_DELAY;
  if (millis() > nextMaintain)
  {
    nextMaintain = millis() + MAINTAIN_DELAY;
    int ret = Ethernet.maintain();
    if (ret == 1 || ret == 3)
    {
      Serial.print("Failed to maintain DHCP lease. Error: ");
      Serial.println(ret);
    }
    Serial.print("Current IP address: ");
    IPAddress myIPAddress = Ethernet.localIP(); 
    Serial.println(myIPAddress);  
  }
}
