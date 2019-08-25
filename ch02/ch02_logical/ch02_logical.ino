void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  if ( digitalRead(2) && digitalRead(3) )
    blink(); // blink of both pins are HIGH

  if ( digitalRead(2) || digitalRead(3) )
    blink(); // blink of either pins is HIGH

  if ( !digitalRead(2)  )
    blink(); // blink of the pin is not HIGH
}

void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
