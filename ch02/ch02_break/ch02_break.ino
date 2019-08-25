/* 
   break sketch
   Demonstrates the use of the break statement
 */

const int sensorPin = A0; // analog input 0
const int switchPin = 2; // digital input 2

void setup()
{ 
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // enable LED pin as output
  pinMode(switchPin, INPUT_PULLUP); // enable button pin as input
}

void loop()
{
  while(analogRead(sensorPin) > 100)
  {
    if(digitalRead(switchPin) == LOW)
    {
      break; // exit the loop if the switch is pressed
    }
    blink(); // call a function to turn an LED on and off
  }
}

void blink()
{
   digitalWrite(LED_BUILTIN, HIGH);
   delay(100); 
   digitalWrite(LED_BUILTIN, LOW);
   delay(100);
}
