/*
   SendBinaryStruct sketch
   Sends a struct as binary data.
*/

typedef struct {
  char padding; // ensure same alignment on 8-bit and 32-bit
  char header;
  short intValue1;
  short intValue2;
} shortMsg;

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  shortMsg myStruct = { 0, 'H', (short) random(599), (short) random(599) };
  sendStructure((byte *)&myStruct, sizeof(myStruct));

  delay(1000);
}

void sendStructure(byte *structurePointer, int structureLength)
{
  int i;
  for (i = 0 ; i < structureLength ; i++) {
    Serial.write(structurePointer[i]);
  }
}
