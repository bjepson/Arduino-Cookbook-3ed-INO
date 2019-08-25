void setup() {
  Serial.begin(9600);
  Serial.println( floor(1) );    // this prints  1.00
  Serial.println( floor(1.1) );  // this prints  1.00
  Serial.println( floor(0) );    // this prints  0.00
  Serial.println( floor(.1) );   // this prints  0.00
  Serial.println( floor(-1) );   // this prints -1.00
  Serial.println( floor(-1.1) ); // this prints -2.00

  Serial.println( ceil(1) );     // this prints  1.00
  Serial.println( ceil(1.1) );   // this prints  2.00
  Serial.println( ceil(0) );     // this prints  0.00
  Serial.println( ceil(.1) );    // this prints  1.00
  Serial.println( ceil(-1) );    // this prints -1.00
  Serial.println( ceil(-1.1) );  // this prints -1.00
  int result = round(1.1);
  Serial.println(result);

}

void loop() {
  // put your main code here, to run repeatedly:

}
