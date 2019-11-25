#include <SPI.h>
#include <ESP8266WiFi.h>
const char ssid[] = "YOUR_SSID";
const char password[] = "YOUR_PASSWORD";
WiFiClient client;
WiFiServer server(80);

bool configureNetwork()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) // Wait for connection
  {
    delay(1000);
    Serial.print("Waiting for connection to "); Serial.println(ssid);
  }
  return true;
}

IPAddress getIP()
{
  return WiFi.localIP();
}

void maintain()
{
  // Do nothing
}
