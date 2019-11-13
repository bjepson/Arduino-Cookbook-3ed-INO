#include <SPI.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>

#define RF69_FREQ 915.0 // Set to a supported frequency 

#define MY_ADDRESS 1 // Address of this node

// Initialize the radio driver
#define RFM69_INT  3 
#define RFM69_CS   4
#define RFM69_RST  2
RH_RF69 rf69(RFM69_CS, RFM69_INT);

// This object manages message delivery
RHReliableDatagram rf69_manager(rf69, MY_ADDRESS);

void setup() 
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);    
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Resetting radio");
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
  
  if (!rf69_manager.init()) 
  {
    Serial.println("Could not start the radio");
    while (1); // halt
  }

  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("Could not set frequency");
    while (1); // halt
  }

  // If you are using a high power version of the RF69 (RFM69HW/HCW), this is required:
  rf69.setTxPower(20, true);  // Power range is from 14-20
  
  // Each node must use the same key.
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);
  
  Serial.print("RFM69 radio running at ");
  Serial.print((int)RF69_FREQ); Serial.println(" MHz");
}

byte message[RH_RF69_MAX_MESSAGE_LEN]; // Buffer to hold message from other device
byte reply[] = "Goodbye!";
void loop() 
{
  if (rf69_manager.available()) // Received a message
  {
    byte len = sizeof(message);
    byte sender; // Sender ID
    if (rf69_manager.recvfromAck(message, &len, &sender)) // Wait for a message
    {
      message[len] = 0; // Add a nul (0) to end of message

      Serial.print("Got ["); Serial.print((char *) message);
      Serial.print("] from "); Serial.println(sender);
      // Blink the LED
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
      
      // Reply to sender
      if (!rf69_manager.sendtoWait(reply, sizeof(reply), sender))
      {
        Serial.print("Failed to deliver message to "); Serial.println(sender);
      }
    }
  }
}
