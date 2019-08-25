/*
  array sketch
  an array of switches controls an array of LEDs
  see #simple_digital_and_analog_input for more on using switches
  see #visual_output for information on LEDs
*/

const int PIN_COUNT = 4;  // define a constant for the number of elements
int inputPins[PIN_COUNT] = {2, 3, 4, 5};
int ledPins[PIN_COUNT] = {10, 11, 12, 13};

void setup()
{
  int empty[4];

  Serial.begin(9600);
  while (!Serial);

  for (int index = 0; index < PIN_COUNT; index++)
  {
    Serial.println(empty[index]);
    pinMode(ledPins[index], OUTPUT);
    pinMode(inputPins[index], INPUT_PULLUP);
  }
}

void loop() {
  int i;
  Serial.print("i = ");
  Serial.println(i);
  for (int index = 0; index < 4; index++)
  {
    int val = digitalRead(inputPins[index]);  // read input value
    if (val == LOW)                           // check if the switch is pressed
    {
      digitalWrite(ledPins[index], HIGH); // LED on if switch is pressed
    }
    else
    {
      digitalWrite(ledPins[index], LOW);  // turn LED off
    }
  }
}
