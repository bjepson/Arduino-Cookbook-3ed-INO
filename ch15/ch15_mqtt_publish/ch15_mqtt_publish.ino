/*
 *  Basic MQTT publish sketch
 */

// Uncomment only one of the following
//#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

#include <PubSubClient.h>

const char* broker = "mqtt.eclipse.org"; // the address of the MQTT broker

const int interval = 5000;   // milliseconds between events
unsigned int timePublished;  // millis time of most recent publish

PubSubClient psclient(client);

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
}

void loop(void)
{
  if (millis() - timePublished > interval) 
  {
    if (!psclient.connected())
      psclient.connect("arduinoCookbook3Pub");
    if (psclient.connected()) 
    {
      int val = analogRead(A0);
      psclient.publish("arck3/alog", String(val).c_str());
      timePublished = millis();
      Serial.print("Published "); Serial.println(val);
    }
  }
  if (psclient.connected())
    psclient.loop();
}
