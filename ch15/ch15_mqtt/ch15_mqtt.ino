#include <SPI.h>
#include <PubSubClient.h>
#include <WiFiNINA.h>

const int buttonPin = 12; // Button connected to pin 12
const int debounceTime = 20; // number of milliseconds for switch to be stable

const char[] ssid = "YOUR SSID";
const char[] password = "YOUR PASSWORD";

IPAddress broker(192,168,1,253);
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) 
{
  if (String(topic).equals("setLED"))
  {
    if (payload[0] == '1')
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (payload[0] == '0')
    {
      digitalWrite(LED_BUILTIN, LOW);      
    }
  }
}

void reconnect() 
{  
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT broker.");
    if (client.connect("ledClient")) 
    {
      Serial.println("Connected.");
      client.subscribe("setLED");
    } 
    else 
    {
      Serial.print("Failed to connect with result code: ");
      Serial.print(client.state());
      delay(5000); // Try again in 5 seconds
    }
  }
}

void setup()
{
  int status = WL_IDLE_STATUS; // WiFistatus

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
   
  if (WiFi.status() == WL_NO_MODULE) 
  {
    Serial.println("Couldn't find Wi-Fi hardware.");
    while(1); // halt
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
  
  // Configure the MQTT client
  client.setServer(broker, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop(); // Process events
  if (digitalRead(buttonPin) == LOW) // Button is pressed
  {
    delay(debounceTime);
    int count = 0;
    while(digitalRead(buttonPin) == LOW)
      count++;
    if (count > 10)
      client.publish("buttonState", "Pressed");

  }
}
