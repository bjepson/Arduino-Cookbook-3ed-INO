void setup() {
  Serial.begin(9600);
  int myValue =  pow(3, 2);
  Serial.println(myValue);
  Serial.println(pow(3, 2)); // this prints 9.00
  int z = pow(3, 2);
  Serial.println(z);        // this prints 9
  float s = pow(2, 1.0 / 12); // the twelfth root of two
  Serial.println(s, 10);

}

void loop() {
  // put your main code here, to run repeatedly:

}
