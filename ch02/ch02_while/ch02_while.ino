/*
 * Repeat
 * blinks while a condition is true
 */

const int sensorPin = A0; // analog input 0

void setup()
{ 
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // enable LED pin as output
}

void loop()
{
  while(analogRead(sensorPin) > 100)
  {
    blink();    // call a function to turn an LED on and off
    Serial.print(".");
  }
  Serial.println(analogRead(sensorPin)); // this is not executed until after
                                         // the while loop finishes!!!
}  

void blink()
{
   digitalWrite(LED_BUILTIN, HIGH);
   delay(100); 
   digitalWrite(LED_BUILTIN, LOW);
   delay(100);
}
