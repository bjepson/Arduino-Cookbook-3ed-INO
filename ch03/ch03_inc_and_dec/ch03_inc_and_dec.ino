void setup() {
  Serial.begin(9600);
  
  int myValue = 0;

  myValue = myValue + 1;  // this adds one to the variable myValue
  myValue += 1;           // this does the same as the above

  myValue = myValue - 1;  // this subtracts one from the variable myValue
  myValue -= 1;           // this does the same as the above

  myValue = myValue + 5;  // this adds five to the variable myValue
  myValue += 5;           // this does the same as the above


  Serial.println(myValue);

}

void loop() {
  // put your main code here, to run repeatedly:

}
