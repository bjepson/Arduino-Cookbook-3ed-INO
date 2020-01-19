/* NFC Tag Writer
 * Look for an NFC tag and display its unique identifier. 
 */

/* 
 * If you are using a module over SPI or I2C, see the PN532_SPI 
 * or PN532_I2C examples for the appropriate preamble.
 */
#include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>
#include <PN532/PN532_HSU/PN532_HSU.h>

PN532_HSU pn532hsu(Serial1);
NfcAdapter nfc(pn532hsu);

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
