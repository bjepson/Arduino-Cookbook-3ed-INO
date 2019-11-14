/*
 * RFM69HCW transmit sketch
 * Receive a message from another module and send a reply.
 */
#include <SPI.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>

#define MY_ADDR 1 // Address of this node

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

struct sensor {
  char header;
  char padding; // ensure same alignment on 8-bit and 32-bit
  unsigned short int pin0;
  unsigned short int pin1;
  unsigned short int pin2;
} sensorStruct;
byte message[sizeof(sensorStruct)]; // define anything you send over the radio channel outside so it's not on the stack
void loop() 
{
  if (rf69_manager.available()) // Received a message
  {
    byte len = sizeof(message);
    byte sender; // Sender ID
    if (rf69_manager.recvfromAck(message, &len, &sender)) // Wait for a message
    {
      memcpy(&sensorStruct, message, len);
      Serial.print("Header: "); Serial.println(sensorStruct.header);
      Serial.print("Sensor 0: "); Serial.println(sensorStruct.pin0);
      Serial.print("Sensor 1: "); Serial.println(sensorStruct.pin1);
      Serial.print("Sensor 2: "); Serial.println(sensorStruct.pin2);
    }
  }
}
