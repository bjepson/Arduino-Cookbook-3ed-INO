void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  float deg = 30;                 // angle in degrees
  float rad  = deg * PI / 180;    // convert to radians
  Serial.println(rad);            // print the radians
  Serial.println(sin(rad), 5);    // print the sine
  Serial.println(cos(rad), 5);    // print the cosine

  {
    rad = deg * DEG_TO_RAD;  // a way to convert degrees to radians

  }

  {
    deg = rad * RAD_TO_DEG;  // a way to convert radians to degrees
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
