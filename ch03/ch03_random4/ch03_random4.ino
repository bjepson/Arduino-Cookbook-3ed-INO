// Random
// demonstrates generating random numbers

#define highWord(w) ((w) >> 16)
#define lowWord(w) ((w) & 0xffff)

long randNumber;

void setup()
{
  Serial.begin(500000);                        // Initialise the Serial port
  while (!Serial);
}

void loop()
{
  int r = random(2147483647);
  int loWord = lowWord(r);
  int hiWord = highWord(r);
  Serial.print((char) highByte(hiWord));
  Serial.print((char) lowByte(hiWord));
  Serial.print((char) highByte(loWord));
  Serial.print((char) lowByte(loWord));
  delay(1);
}
