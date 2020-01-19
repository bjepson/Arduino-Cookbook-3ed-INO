/* NFC Tag Scanner - I2C
 * Look for an NFC tag and display its unique identifier. 
 */
 
#include <Wire.h>
#include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>
#include <PN532/PN532_I2C/PN532_I2C.h>

PN532_I2C pn532i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532i2c);

void setup() 
{
  Serial.begin(9600);
  nfc.begin(); // Initialize the NFC reader
}

void loop() 
{
  Serial.println("Waiting for a tag");
  if (nfc.tagPresent()) // If the reader sees an NFC tag
  {
    NfcTag tag = nfc.read(); // read the NFC tag
    Serial.println(tag.getUidString()); // Display its id
  }
  delay(500);
}
