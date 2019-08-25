
#define highWord(w) ((w) >> 16)
#define lowWord(w) ((w) & 0xffff)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  long longValue = 16909060;
  int loWord = lowWord(longValue);
  int hiWord = highWord(longValue);
  Serial.println(loWord,DEC);
  Serial.println(hiWord,DEC);

  delay(10000);
}
