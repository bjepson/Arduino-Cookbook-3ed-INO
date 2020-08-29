/*
 * UDPSendReceiveStrings
 * This sketch receives UDP message strings, prints them to the serial port
 * and sends an "acknowledge" string back to the sender
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <EthernetUdp.h> 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC address to use

unsigned int localPort = 8888; // local port to listen on

const int maxBufferLength = 24;

// buffers for receiving and sending data
char packetBuffer[maxBufferLength]; // buffer to hold incoming packet,
char replyBuffer[] = "acknowledged";       // a string to send back

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() 
{
  Serial.begin(9600);

  // start Ethernet and UDP
  Ethernet.begin(mac);
  Udp.begin(localPort);
}

void loop() 
{
  // if there's data available, read a packet
  int packetSize =  Udp.parsePacket(); 
  if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);

    // read packet into packetBuffer and get sender's IP addr and port number
    Udp.read(packetBuffer, maxBufferLength);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a string back to the sender
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyBuffer);
    Udp.endPacket();
  }
  maintainLease(); // Keep our DHCP connection
  delay(10);
}

#define MAINTAIN_DELAY 750 // Maintain DHCP lease every .75 seconds
void maintainLease()
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
