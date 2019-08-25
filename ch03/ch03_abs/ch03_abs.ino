void setup() {
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  Serial.println(x);
  Serial.println(y);

  if (abs(x - y) > 10)
  {
    Serial.println("The analog values differ by more than 10");
  }
  delay(250);
}
