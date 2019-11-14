/*
 * RFM69HCW transmit sketch
 * Send a message to another module and look for a reply.
 */
#include <SPI.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>

#define MY_ADDR   2 // Address of this node
#define DEST_ADDR 1 // The other node

#define RF69_FREQ 915.0 // Set to a supported frequency 

// Define the radio driver
#define RFM69_INT  3 
#define RFM69_CS   4
#define RFM69_RST  2
RH_RF69 rf69(RFM69_CS, RFM69_INT);

// This object manages message delivery
RHReliableDatagram rf69_manager(rf69, MY_ADDR);

void setup() 
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Resetting radio");
  digitalWrite(RFM69_RST, HIGH); delay(10);
  digitalWrite(RFM69_RST, LOW); delay(10);
  
  if (!rf69_manager.init()) 
  {
    Serial.println("Could not start the radio");
    while (1); // halt
  }

  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("Could not set frequency");
    while (1); // halt
  }

  // If you are using a high power version of the RF69 (RFM69HW/HCW), 
  // the following is required:
  rf69.setTxPower(20, true);  // Power range is from 14-20
  
  // Each node must use the same key.
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);
  
  Serial.print("RFM69 radio running at ");
  Serial.print((int)RF69_FREQ); Serial.println(" MHz");
}

byte response[RH_RF69_MAX_MESSAGE_LEN]; // Buffer to hold message from other device
byte message[] = "Hello!";
void loop() 
{
  delay(1000); // Wait 1 second

  if (rf69_manager.sendtoWait((byte *)message, strlen(message), DEST_ADDR))
  {
    byte len = sizeof(response);
    byte sender; // Sender ID

    // Wait for a reply
    if (rf69_manager.recvfromAckTimeout(response, &len, 2000, &sender)) 
    {
      response[len] = 0; // Add a nul (0) to end of response

      Serial.print("Got ["); Serial.print((char *) response);
      Serial.print("] from "); Serial.println(sender);

      // Blink the LED
      digitalWrite(LED_BUILTIN, HIGH); delay(250);
      digitalWrite(LED_BUILTIN, LOW); delay(250);
    } 
    else 
    {
      Serial.print("Received no reply from "); Serial.println(sender);
    }
  } 
  else 
  {
    Serial.print("Failed to send message to "); Serial.println(DEST_ADDR);
  }
}
