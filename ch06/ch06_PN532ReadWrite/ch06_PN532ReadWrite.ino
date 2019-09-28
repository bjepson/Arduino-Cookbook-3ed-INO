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
    tag.print(); // print whatever is currently on it

    // Give the user time to avoid writing to the tag
    Serial.print("Countdown to writing the tag: 3");
    for (int i = 2; i >= 0; i--) {
      delay(1000);
      Serial.print("..."); Serial.print(i);
    }
    Serial.println();
    
    // Write a message to the tag
    NdefMessage message = NdefMessage();
    message.addUriRecord("http://oreilly.com");
    bool success = nfc.write(message);
    if (!success)
      Serial.println("Write failed.");
    else
      Serial.println("Success.");
  }
  delay(500);
}
