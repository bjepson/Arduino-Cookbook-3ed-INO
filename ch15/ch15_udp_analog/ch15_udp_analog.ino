/*
 *  UDPSendReceive with analog output sketch
*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUDP.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC address to use

unsigned int localPort = 8888;      // local port to listen on

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; // buffer to hold incoming packet,
int packetSize; // holds received packet size

const int analogOutPins[] = { 3, 5, 6, 9 }; // pins 10 and 11 used by Ethernet shield

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() 
{
  Ethernet.begin(mac);
  Udp.begin(localPort);

  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() 
{
  // if there's data available, read a packet
  packetSize = Udp.parsePacket();
  if (packetSize > 0)
  {
    Serial.print("Received packet of size ");
    Serial.print(packetSize);
    Serial.println(" with contents:");
    // read packet into packetBuffer and get sender's IP addr and port number
    packetSize = min(packetSize, UDP_TX_PACKET_MAX_SIZE);
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    for ( int i = 0; i < packetSize; i++)
    {
      byte value = packetBuffer[i];
      if (i < 4)
      {
        // only write to the first four analog out pins
        analogWrite(analogOutPins[i], value);
      }
      Serial.println(value, DEC);
    }
    Serial.println();
    // tell the sender the values of our analog ports
    sendAnalogValues(Udp.remoteIP(), Udp.remotePort());
  }
  maintainLease();
  // wait a bit
  delay(10);
}

void sendAnalogValues( IPAddress targetIp, unsigned int targetPort )
{
  Serial.println("Preparing packet");
  int index = 0;
  for (int i = 0; i < 6; i++)
  {
    int value = analogRead(i);

    packetBuffer[index++] = lowByte(value);  // the low byte)
    packetBuffer[index++] = highByte(value); // the high byte)
  }

  Serial.println(packetBuffer);
  // send a packet back to the sender
  Udp.beginPacket(targetIp, targetPort);
  Udp.write(packetBuffer);
  Udp.endPacket();
  Serial.println("Packet sent");
}

#define MAINTAIN_DELAY 750 // Maintain DHCP lease every .75 seconds
void maintainLease()
{
  static unsigned long nextMaintain = millis() + MAINTAIN_DELAY;
  if (millis() > nextMaintain)
  {
      Serial.print("Maintain ");
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
