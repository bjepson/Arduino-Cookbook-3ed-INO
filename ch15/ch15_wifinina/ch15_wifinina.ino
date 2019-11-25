/*
 * WiFiNINA Web Client sketch
 * Requests some data from the Internet Archive
 */

#include <SPI.h>
#include <WiFiNINA.h>

const char ssid[] = "YOUR_SSID";
const char password[] = "YOUR_PASSWORD";

WiFiClient client; // WiFi client

char serverName[] = "archive.org";
String request = "GET /advancedsearch.php?q=arduino&fl%5B%5D=description"
                 "&rows=1&sort%5B%5D=downloads+desc&output=csv#raw HTTP/1.0";

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

void setup()
{
  Serial.begin(9600);
  if (!configureNetwork())
  {
    Serial.println("Stopping.");
    while(1); // halt
  }
  
  Serial.println("Connecting to server...");
  int ret = client.connect(serverName, 80); 
  if (ret == 1) 
  {
    Serial.println("Connected");
    client.println(request);
    client.print("Host: "); client.println(serverName);
    client.println("Connection: close");
    client.println();
  } 
  else 
  {
    Serial.println("Connection failed, error was: ");
    Serial.print(ret, DEC);
  }
}

void loop()
{
  if (client.available()) 
  {
    char c = client.read();
    Serial.print(c);  // echo all data received to the Serial Monitor
  }
  if (!client.connected()) 
  {
    Serial.println();
    Serial.println("Disconnecting.");
    client.stop();
    while(1); // halt
  }
}
