#include <SPI.h>
#include <ESP8266WiFi.h>
const char ssid[] = "YOUR_SSID";
const char password[] = "YOUR_PASSWORD";
WiFiClient client;
bool configureNetwork()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) // Wait for connection
  {
    delay(500);
    Serial.print("Waiting for connection to "); Serial.println(ssid);
  }
  return true;
}
