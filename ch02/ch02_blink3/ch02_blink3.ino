/*
  blink3 sketch
  Demonstrates calling a function with a parameter and returning a value.
  Uses the same wiring as the pull-up sketch from
  #using_a_switch_without_external_resis

  The LED flashes when the program starts and stops when a switch connected
  to digital pin 2 is pressed.
  The program prints the number of times that the LED flashes.
*/

const int inputPin = 2;         // input pin for the switch

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(inputPin, INPUT);
  digitalWrite(inputPin, HIGH); // use internal pull-up resistor (Recipe 5.2)
  Serial.begin(9600);
}

void loop() {
  Serial.println("Press and hold the switch to stop blinking");
  int count = blink3(250); // blink the LED 250ms on and 250ms off
  Serial.print("The number of times the switch blinked was ");
  Serial.println(count);
  while (digitalRead(inputPin) == LOW)
  {
    // do nothing until they let go of the button
  }

  // print the percent value of 6 analog pins
  for (int sensorPin = 0; sensorPin < 6; sensorPin++)
  {
    Serial.print("Percent of sensor on pin ");
    Serial.print(sensorPin);
    Serial.print(" is ");
    int val = sensorPercent(sensorPin);
    Serial.println(val);
  }
}

// blink an LED using the given delay period
// return the number of times the LED flashed
int blink3(int period)
{
  int result = 0;

  while (digitalRead(inputPin) == HIGH) // repeat until switch is pressed
    // (it will go low when pressed)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(period);
    digitalWrite(LED_BUILTIN, LOW);
    delay(period);
    result = result + 1; // increment the count
  }
  // here when switchVal is no longer HIGH because the switch is pressed
  return result;  // this value will be returned
}

int sensorPercent(int pin)
{
  int percent;

  int val = analogRead(pin);  // read the sensor (ranges from 0 to 1023)
  return map(val, 0, 1023, 0, 100); // percent will ranges from 0 to 100.

}
