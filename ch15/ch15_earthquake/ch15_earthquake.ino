/*
   WiFiNINA example
   Earthquake warning system using MKR WiFi 1010 or Uno WiFi Rev2
*/

#include <SPI.h>
#include <WiFiNINA.h>
#include <TimeLib.h>

const char ssid[] = "YOUR SSID";
const char password[] = "YOUR PASSWORD";

const char server[] = "earthquake.usgs.gov";
const char path_query[] = "/fdsnws/event/1/query?format=geojson&maxradiuskm=300&limit=5";

const float latitude  = 41.5801;
const float longitude = -71.4774;

WiFiSSLClient client; // SSL-capable client

void setup()
{
  int status = WL_IDLE_STATUS; // WiFistatus

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Couldn't find Wi-Fi hardware.");
    while (1); // halt
  }

  while (status != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, password); // Attempt WPA/WPA2 connection

    delay(5000); // Wait 5 seconds
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
}

#define INTERVAL (1000L * 60 * 60 * 1) // 60 seconds * 60 minutes * 1 hour
unsigned long nextRequestTime = millis();
void loop()
{
  if (millis() > nextRequestTime && !client.connected())
  {
    checkQuakes();
    nextRequestTime = millis() + INTERVAL;
  }
}

unsigned long getTimeValue(char marker[])
{
    // Look for the marker
    if (!client.find(marker)) 
    {
      Serial.print(F("Could not find marker in response:"));
      Serial.println(marker);
      return 0;
    }
    
    // Read the time as a string because it's too large for parseInt.
    String millisTime = client.readStringUntil(',');
    String secondsTime = millisTime.substring(0, millisTime.length() - 3);;
    return secondsTime.toInt();
}

void checkQuakes()
{
  if (client.connect(server, 443))
  {
    Serial.println(F("Connected"));

    String requestHeader = String("GET ") + path_query + "&latitude=" + latitude + "&longitude=" + longitude + " HTTP/1.0";
    client.println(requestHeader);
    client.println(String("Host: ") + server);
    client.println("Connection: close");
    client.println();

    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status + 9, "200 OK") != 0) {
      Serial.print(F("HTTP Error "));
      Serial.println(status);
      return;
    }

    long responseTime = getTimeValue("\"generated\":");
    if (!responseTime)
      return;

    // Find the first earthquake report
    if (!client.find("\"type\":\"Feature\""))
    {
      Serial.println(F("No recent earthquake near that location."));
      return;
    }
    
    long quakeTime = getTimeValue("\"time\":");
    if (!quakeTime)
      return;
   
    float daysSince = (responseTime - quakeTime) / (60L * 60 * 24);
    Serial.print(daysSince);
    Serial.println(" days since last earthquake");
  }
}
