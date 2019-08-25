void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); // enable LED pin as output

}

void loop() {
  // put your main code here, to run repeatedly:
  blink1();
  delay(1000);
  blink2(5);
}

// blink an LED once
void blink1()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on
  delay(500);                      // wait 500 milliseconds
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off
  delay(500);                      // wait 500 milliseconds
}

// blink an LED the number of times given in the count parameter
void blink2(int count)
{
  while (count > 0 ) // repeat until count is no longer greater than zero
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on
    delay(250);                      // wait 500 milliseconds
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off
    delay(250);                      // wait 500 milliseconds
    count = count - 1; // decrement count
  }
}
