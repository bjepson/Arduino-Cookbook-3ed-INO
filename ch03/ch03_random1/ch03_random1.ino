void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  int minr = 50;
  int maxr = 100;

  while (!Serial);
  {
    long randnum = random(maxr);      // random number between 0 and maxr -1
    Serial.println(randnum);
  }
  {
    long randnum = random(minr, maxr); // random number between minr and maxr -1
    Serial.println(randnum);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
