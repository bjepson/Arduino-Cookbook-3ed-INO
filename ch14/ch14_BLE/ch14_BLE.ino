/*
 * ArduinoBLE sketch
 * Allows control of the onboard LED over Bluetooth Low Energy
 */

#include <ArduinoBLE.h>

#define SERVICE_ID "19B10010-E8F2-537E-4F6C-D104768A1214"
#define CHAR_ID    "19B10011-E8F2-537E-4F6C-D104768A1214"

// Create the service ID and the characteristic (read-write)
BLEService ledService(SERVICE_ID); 
BLEByteCharacteristic ledCharacteristic(CHAR_ID, BLERead | BLEWrite); 
BLEDescriptor ledDescriptor("2901", "LED state");

void setup() 
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  if (!BLE.begin()) 
  {
    Serial.println("Failed to start BLE");
    while (1); // halt
  }

  // Set the name and add the ledService as an advertised service
  BLE.setLocalName("RemoteLED");
  BLE.setAdvertisedService(ledService);

  // Add the descriptor to the characteristic
  ledCharacteristic.addDescriptor(ledDescriptor);
  
  // Add the characteristic to the service
  ledService.addCharacteristic(ledCharacteristic);
  BLE.addService(ledService); // Add the service to the BLE system

  ledCharacteristic.writeValue(0); // Init to 0

  BLE.advertise();
}

void loop() 
{
  BLE.poll();
  
  if (ledCharacteristic.written()) 
  {
    if (ledCharacteristic.value()) 
    {
      digitalWrite(LED_BUILTIN, HIGH);
    } 
    else 
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
