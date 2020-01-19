/* NFC Tag Scanner - Serial
 * Look for an NFC tag and display its unique identifier. 
 */
 
#include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>
#include <PN532/PN532_HSU/PN532_HSU.h>

PN532_HSU pn532hsu(Serial1);
NfcAdapter nfc(pn532hsu);

void setup() 
{
  Serial.begin(9600);
  while (!Serial);

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
