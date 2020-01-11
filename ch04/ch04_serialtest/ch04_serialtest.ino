void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  //while (!Serial) delay(10);
  delay(800);
  //Serial2.begin(9600);
  Serial.println("Hello!");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  Serial.print("U");
  Serial1.print("T");
  delay(1000);
}
