/*
 *  Basic MQTT subscribe sketch
 */

// Uncomment only one of the following
//#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

#include <PubSubClient.h>

const char* broker = "mqtt.eclipse.org"; // the address of the MQTT broker
const int interval = 5000;               // milliseconds between events
unsigned int timePublished;              // time of most recent publish

PubSubClient psclient(client);

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message on topic [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0; i < length; i++) 
  {
    Serial.write(payload[i]);
  }
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  if (!configureNetwork()) // Start the network
  {
    Serial.println("Failed to configure the network");
    while(1)
      delay(0); // halt; ESP8266 does not like ∞ loop without a delay
  }
  psclient.setServer(broker, 1883);
  psclient.setCallback(callback);
}

void loop(void)
{

  if (!psclient.connected()) 
  {
    if (psclient.connect("arduinoCookbook3Sub")) 
    {    
      Serial.println("Subscribing to arck3/alog");
      psclient.subscribe("arck3/alog");
    }
  }
  if (psclient.connected())
    psclient.loop();
}
