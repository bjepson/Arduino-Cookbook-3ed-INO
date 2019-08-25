void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int x = 6;
  x = x << 1;  // 6  shifted left once is 12
  Serial.println(x);
  x = x >> 2;   // 12 shifted right twice is 3
  Serial.println(x);

  delay(10000);
}
