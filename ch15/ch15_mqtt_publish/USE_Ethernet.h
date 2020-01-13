#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;
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
