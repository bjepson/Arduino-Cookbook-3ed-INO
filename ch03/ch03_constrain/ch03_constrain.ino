void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int myValue = analogRead(A0);

  int myConstrainedValue  = constrain(myValue, 100, 200);

}
