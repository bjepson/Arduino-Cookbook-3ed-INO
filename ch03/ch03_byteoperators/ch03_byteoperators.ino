// ByteOperators

int intValue = 258; // 258 in hexadecimal notation is 0x102

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int loWord,hiWord;
  byte loByte, hiByte;


  hiByte = highByte(intValue);
  loByte = lowByte(intValue);

  Serial.println(intValue,DEC);
  Serial.println(intValue,HEX);
  Serial.println(loByte,DEC);
  Serial.println(hiByte,DEC);

  delay(10000); // wait a very long time
}
