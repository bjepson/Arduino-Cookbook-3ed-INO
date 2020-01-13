/*
 * ThingTweet Sketch: post tweet when switch on pin 2 is pressed
*/

// Uncomment only one of the following
//#include "USE_NINA.h"     // WiFiNINA boards
//#include "USE_Ethernet.h" // Ethernet
//#include "USE_ESP8266.h"  // ESP8266 boards

char *thingtweetAPIKey = "YourThingTweetAPIKey";  // your ThingTweet API key
char serverName[] = "api.thingspeak.com";

bool MsgSent = false;
const int btnPin = 2;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  if (!configureNetwork()) // Start the network
  {
    Serial.println("Failed to configure the network");
    while (1)
      delay(0); // halt; ESP8266 does not like ∞ loop without a delay
  }
  pinMode(btnPin, INPUT_PULLUP);
  delay(1000);
  Serial.println("Ready");
}

void loop()
{
  if (digitalRead(btnPin) == LOW) // here if button is pressed
  {
    if (MsgSent == false) // check if message already sent
    {
      MsgSent = sendMessage("I pressed a button on something #thingspeak");
      if (MsgSent)
        Serial.println("Tweeted successfully");
      else
        Serial.println("Unable to Tweet");
    }
  }
  else
  {
    MsgSent = false;  // Button is not pressed
  }
  delay(100);
}

bool sendMessage(char *message)
{
  bool result = false;

  const int tagLen = 16; // the number of tag character used to frame the message
  int msgLen = strlen(message) + tagLen + strlen(thingtweetAPIKey);
  Serial.println("Connecting ...");
  if (client.connect(serverName, 80) )
  {
    Serial.println("Making POST request...");
    client.println("POST /apps/thingtweet/1/statuses/update HTTP/1.1");
    client.print("Host: "); client.println(serverName);
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: "); client.println(msgLen);
    client.println();
    client.print("api_key=");          // msg tag
    client.print(thingtweetAPIKey);    // api key
    client.print("&status=");          // msg tag
    client.print(message);             // the message
    client.println();
  }
  else 
  {
    Serial.println("Connection failed");
  }
  // response string
  if (client.connected())
  {
    Serial.println("Connected");
    if (client.find("HTTP/1.1") && client.find("200 OK") ) {
      result = true;
    }
    else
      Serial.println("Dropping connection - no 200 OK");
  }
  else
  {
    Serial.println("Disconnected");
  }
  client.stop();
  client.flush();

  return result;
}
