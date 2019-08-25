int mult(int a, int b) {
  //int c = (a << 1) + (b >> 2); //add (a times 2) plus ( b divided by 4)
  int c = (a * 3) + (b / 4); //add (a times 3) plus ( b divided by 4)
  return c;
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int a = 0; a <= 10; a++) {
    for (int b = 0; b <= 20; b++) {
      Serial.println(mult(a, b));
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
