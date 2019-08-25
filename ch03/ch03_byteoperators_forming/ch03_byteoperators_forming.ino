// Forming an int or long with byte operations

int intValue = 0x102;  // 258

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int aWord;
  byte loByte, hiByte;

  hiByte = highByte(intValue);
  loByte = lowByte(intValue);

  Serial.println(intValue,DEC);
  Serial.println(loByte,DEC);
  Serial.println(hiByte,DEC);

  aWord = word(hiByte, loByte); // convert the bytes back into a word
  Serial.println(aWord,DEC);
  delay(10000); // wait a very long time
}
