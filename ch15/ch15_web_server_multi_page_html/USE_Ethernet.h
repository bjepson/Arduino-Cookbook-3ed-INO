#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;
EthernetServer server(80);

bool configureNetwork()
{
  if (Ethernet.begin(mac))
  {
    delay(1000); // give the Ethernet module a second to initialize
    return true;
  }
  else
  {
    return false;
  }
}

IPAddress getIP()
{
  return Ethernet.localIP();
}

#define MAINTAIN_DELAY 750 // Maintain DHCP lease every .75 seconds
void maintain()
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
  }
}
