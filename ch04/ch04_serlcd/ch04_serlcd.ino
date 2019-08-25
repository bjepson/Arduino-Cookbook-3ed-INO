void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
}

void loop() {
  Serial1.write(254); // move cursor to beginning of first line
  Serial1.write(128);

  Serial1.write("                "); // clear display
  Serial1.write("                ");

  Serial1.write(254); // move cursor to beginning of first line
  Serial1.write(128);

  Serial1.write("Hello, world!");
  delay(1000);

}
