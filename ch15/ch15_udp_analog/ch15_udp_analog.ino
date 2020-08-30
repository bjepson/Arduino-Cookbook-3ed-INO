/*
 *  UDPSendReceive with analog output sketch
 */

#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h> 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC address to use

unsigned int localPort = 8888;      // local port to listen on

const int maxBufferLength = 24;

byte packetBuffer[maxBufferLength]; // buffer to hold incoming/outgoing packet
int packetSize; // holds received packet size

const int analogOutPins[] = { 3,5,6,9 };  

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  Ethernet.begin(mac);
  Udp.begin(localPort);
  
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {
  // if there's data available, read a packet
  packetSize = Udp.parsePacket(); 
  if(packetSize > 0)
  {
    Serial.print("Received packet of size ");
    Serial.print(packetSize);
    Serial.println(" with contents:");
    // read packet into packetBuffer and get sender's IP addr and port number
    packetSize = min(packetSize, maxBufferLength);
    Udp.read(packetBuffer, maxBufferLength);

    for( int i=0; i < packetSize; i++)
    {
        byte value = packetBuffer[i];
        if( i < 4)
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
  maintainLease(); // Keep our DHCP connection
  // wait a bit
  delay(10);
}

int analogPins[] = {A0, A1, A2, A3, A4, A5};
void sendAnalogValues( IPAddress targetIp, unsigned int targetPort )
{
  int len = sizeof(analogPins) / sizeof(analogPins[0]);
  Serial.println("Preparing packet");
  for(int i = 0; i < len; i++) // Analog pins 0-5
  {
     int value = analogRead(analogPins[i]);
     
     // Map a 10-bit int to an 8-bit byte
     packetBuffer[i] = (byte) map(value, 0, 1023, 0, 255); 
     Serial.println(packetBuffer[i]);
  }

  // send a packet back to the sender
  Udp.beginPacket(targetIp, targetPort);
  Udp.write(packetBuffer, len);
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
