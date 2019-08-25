void setup() {
  Serial.begin(9600);
  int myValue = analogRead(A0);
  int myMinValue = min(myValue, 200);  // myMinValue will be the smaller of
                                       // myVal or 200

  int myMaxValue = max(myValue, 100);  // myMaxValue will be the larger of
                                       // myVal or 100
  Serial.println(myMinValue);
  Serial.println(myMaxValue);

  {
    // myMinValue will be the smaller of the three analog readings:
    int myMinValue = min(analogRead(0), min(analogRead(1), analogRead(2)) );
    Serial.println(myMinValue);
  }

  {
    int myMaxValue = max(analogRead(0), max(analogRead(1), 
                                        max(analogRead(2), analogRead(3))));
    Serial.println(myMaxValue);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
