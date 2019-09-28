/* NFC Tag Scanner
 * Look for an NFC tag and display its unique identifier. 
 */

#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);

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
