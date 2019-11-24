#include <SPI.h>
#include <WiFiNINA.h>
const char ssid[] = "YOUR_SSID";
const char password[] = "YOUR_PASSWORD";
WiFiClient client;

bool configureNetwork()
{
  int status = WL_IDLE_STATUS; // WiFistatus

  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Couldn't find Wi-Fi hardware.");
    return false;
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the Wi-Fi firmware");
  }
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting Wi-Fi connection to "); Serial.println(ssid);
    status = WiFi.begin(ssid, password); // Attempt connection until successful
    delay(1000); // Wait 1 second
  }
  return true;
}
