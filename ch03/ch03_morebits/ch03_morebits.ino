void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = bitRead(2, 1); // returns 1 : 2 is binary 10 and bit in position 1 is 1
  Serial.println(a);
  int b = bitRead(4, 1); // returns 0 : 4 is binary 100 and bit in position 1 is 0
  Serial.println(b);
  Serial.println(bit(0));
  Serial.println(bit(1));
  Serial.println(bit(2));
  Serial.println(bit(7));
  delay(10000);
}
