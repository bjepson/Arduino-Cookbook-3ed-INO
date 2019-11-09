/*
 * I2C EEPROM sketch
 * Reads data from and writes data to an 24LC128
 */
#include <Wire.h>

const byte EEPROM_ID = 0x50; // I2C address for 24LC128 EEPROM

// first human-readable ASCII character '!' is number 33:
int thisByte = 33;

void setup()
{
  Serial.begin(9600);
  while(!Serial); // Required on Leonardo and most ARM-based boards
  Wire.begin();

  Serial.println("Writing 1024 bytes to EEPROM");
  for (int i=0; i < 1024; i++)
  {
    I2CEEPROM_Write(i, thisByte);
    // go on to the next character
    thisByte++;
    if (thisByte == 126)   // you could also use if (thisByte == '~')
      thisByte = 33;     // start over
  }

  Serial.println("Reading 1024 bytes from EEPROM");
  int thisByte = 33;
  for (int i=0; i < 1024; i++)
  {
    char c = I2CEEPROM_Read(i);
    if(c != thisByte)
    {
      Serial.println("read error");
      break;
    }
    else
    {
      Serial.print(c);
    }
    thisByte++;
    if(thisByte == 126)
    {
      Serial.println();
      thisByte = 33;     // start over on a new line
    }
  }
  Serial.println();
  Serial.println("Done.");
}

void loop()
{

}

// This function is similar to Arduino's EEPROM.write()
void I2CEEPROM_Write(unsigned int address, byte data)
{
  Wire.beginTransmission(EEPROM_ID);
  Wire.write((int)highByte(address));
  Wire.write((int)lowByte(address));
  Wire.write(data);
  Wire.endTransmission();

  delay(5); // wait for the I2C EEPROM to complete the write cycle
}

// This function is similar to EEPROM.read()
byte I2CEEPROM_Read(unsigned int address )
{
  byte data;

  Wire.beginTransmission(EEPROM_ID);
  Wire.write((int)highByte(address));
  Wire.write((int)lowByte(address));
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ID,(byte)1);
  while(Wire.available() == 0) // wait for data
    ;
  data = Wire.read();
  return data;
}
