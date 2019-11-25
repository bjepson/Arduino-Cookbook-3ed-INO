/*
   Web Client DNS sketch
*/

#include <SPI.h>

#define USE_WIFININA // Uno WiFI R2, MKR1010, Nano IoT, TK
//#define USE_ESP8266 // ESP8266 Platform
//#define USE_ETHERNET // Ethernet

#ifdef USE_WIFININA
#include <WiFiNINA.h>
#endif

#ifdef USE_ESP8266
#include <ESP8266WiFi.h>
#endif

#if defined(USE_WIFININA) || defined(USE_ESP8266)
const char ssid[] = "YOUR SSID";
const char password[] = "YOUR PASSWORD";
WiFiClient client;
#endif

#ifdef USE_ETHERNET
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;
#endif

bool configureNetwork()
{
  bool success = false;

#ifdef USE_WIFININA
  int status = WL_IDLE_STATUS; // WiFistatus

  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Couldn't find Wi-Fi hardware.");
    while (1); // halt
  }
  if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the Wi-Fi firmware");
  }
  while (status != WL_CONNECTED)
  {
    Serial.print("Connecting to "); Serial.println(ssid);
    status = WiFi.begin(ssid, password); // Attempt connection until successful
    delay(1000); // Wait 1 second
  }
  success = true;
#endif

#ifdef USEESP8266
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) // Wait for connection
  {
    delay(500);
    Serial.print("Waiting for connection to "); Serial.println(ssid);
  }
  success = true;
#endif

#ifdef USE_ETHERNET
  success = (0 == Ethernet.begin(mac));
  delay(1000); // give the Ethernet module a second to initialize
#endif

  return success;
}

char serverName[] = "www.google.com";

void setup()
{
  Serial.begin(9600);
  if (!configureNetwork()) { // Start the network
    Serial.println("Failed to configure the network");
    while (true); // halt
  }

  int ret = client.connect(serverName, 80);
  if (ret == 1) {
    Serial.println("connected"); //  report successful connection
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  }
  else {
    Serial.println("connection failed, err: ");
    Serial.print(ret, DEC);
  }
}

void loop()
{
  // Read and print incoming butes from the server:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // stop the client if disconnected:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    while (true) ; // endless loop
  }
}
