/*
 * Solenoid sketch
 */
int solenoidPin = 2;            // Solenoid connected to transistor on pin 2

void setup()
{
  pinMode(solenoidPin, OUTPUT);
}

void loop()
{
  long interval = 1000 * 60 * 60 ;   // interval = 60 minutes
  
  digitalWrite(solenoidPin, HIGH); // activates the solenoid
  delay(1000);                     // waits for a second
  digitalWrite(solenoidPin, LOW);  // deactivates the solenoid
  delay(interval);                 // waits one hour
}
