/*
  PulseIn sketch
  displays duration of high and low pulses from analogWrite
 */

const int inputPin = 3;   // analog output pin to monitor
unsigned long val;  // this will hold the value from pulseIn

void setup()
{  
  Serial.begin(9600);
}

void loop()
{
  analogWrite(inputPin, 128);
  Serial.print("Writing 128 to pin ");
  Serial.print(inputPin);
  printPulseWidth(inputPin);
  
  analogWrite(inputPin, 254);
  Serial.print("Writing 254 to pin ");
  Serial.print(inputPin);
  printPulseWidth(inputPin);
  delay(3000);
}

void printPulseWidth(int pin)
{
   val = pulseIn(pin, HIGH);
   Serial.print(": High Pulse width = "); 
   Serial.print(val);
   val = pulseIn(pin, LOW);
   Serial.print(", Low Pulse width = "); 
   Serial.println(val); 
}
