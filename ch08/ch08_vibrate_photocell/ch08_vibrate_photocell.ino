/*
 * Vibrate_Photocell sketch
 * Vibrate when photosensor detects light above ambient level
 */

const int motorPin  = 3;  // vibration motor transistor is connected to pin 3
const int sensorPin = A0; // Photodetector connected to analog input 0
int sensorAmbient = 0;             // ambient light level (calibrated in setup)
const int thresholdMargin = 100;   // how much above ambient needed to vibrate

void setup()
{
  pinMode(motorPin, OUTPUT);
  sensorAmbient = analogRead(sensorPin); // get startup light level
}

void loop()
{
  int sensorValue = analogRead(sensorPin);
  if( sensorValue > sensorAmbient + thresholdMargin)
  {
    digitalWrite(motorPin,  HIGH); //vibrate
  }
  else
  {
    digitalWrite(motorPin,  LOW);   // stop vibrating
  }
}
