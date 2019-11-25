/*
 * UdpNtp sketch
 * Get the time from an NTP time server
 * Demonstrates use of UDP sendPacket and ReceivePacket
 */

#include <SPI.h>   
#include <Ethernet.h>

#include <EthernetUDP.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // MAC address to use

unsigned int localPort = 8888;      // local port to listen for UDP packets

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

//IPAddress timeServer(132, 163, 96, 5); // ntp-b.nist.gov NTP server
const int NTP_PACKET_SIZE= 48; // NTP time stamp is in the first 48 
                               // bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; // buffer to hold incoming/outgoing packets

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup()
{
  Serial.begin(9600);
  // start Ethernet and UDP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    while(1); // halt
  }
  Udp.begin(localPort);
}

void loop()
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  if ( Udp.parsePacket() ) 
  { 
    Serial.println("parsed");
    Udp.read(packetBuffer,NTP_PACKET_SIZE);  // read packet into buffer

    //the timestamp starts at byte 40, convert four bytes into a long integer
    unsigned long hi = word(packetBuffer[40], packetBuffer[41]);
    unsigned long low = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = hi << 16 | low;  // this is NTP time 
                                                    // (seconds since Jan 1 1900)

    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);

    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970
    const unsigned long seventyYears = 2208988800UL;     
    unsigned long epoch = secsSince1900 - seventyYears;  // subtract 70 years
    Serial.println(epoch);                               // print Unix time

    // print the hour, minute and second:
    // UTC is the time at Greenwich Meridian (GMT)
    Serial.print("The UTC time is ");       
    // print the hour (86400 equals secs per day)
    Serial.print((epoch  % 86400L) / 3600); 
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) 
    {
      // Add leading zero for the first 10 minutes of each hour
      Serial.print('0');
    }
    // print the minute (3600 equals secs per minute)
    Serial.print((epoch  % 3600) / 60);
    Serial.print(':');
    if ( (epoch % 60) < 10 ) 
    {
      // Add leading zero for the first 10 seconds of each minute
      Serial.print('0');
    }
    Serial.println(epoch %60); // print the second
  }
  // wait ten seconds before asking for the time again
  delay(10000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  memset(packetBuffer, 0, NTP_PACKET_SIZE);  // set all bytes in the buffer to 0

  // Initialize values needed to form NTP request
  packetBuffer[0] = B11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum
  packetBuffer[2] = 6;     // Max Interval between messages in seconds
  packetBuffer[3] = 0xEC;  // Clock Precision
  // bytes 4 - 11 are for Root Delay and Dispersion and were set to 0 by memset
  packetBuffer[12]  = 49;  // four byte reference ID identifying
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:        
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket();
}
