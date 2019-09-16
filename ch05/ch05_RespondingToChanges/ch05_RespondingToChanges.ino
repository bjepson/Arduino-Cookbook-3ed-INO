/*
 * RespondingToChanges sketch
 * flash an LED to indicate low voltage levels
 */

long batteryFull       = 1500;  // millivolts for a full battery
long warningThreshold  = 1200;  // Warning level in millivolts - LED flashes
long criticalThreshold = 1000;  // Critical voltage level - LED stays on

const int batteryPin = A0;
const int ledPin = LED_BUILTIN;

void setup()
{
   pinMode(ledPin, OUTPUT);
}

void loop()
{
  int val = analogRead(batteryPin);    // read the value from the sensor
  int mv = map(val, 0, 1023, 0, 5000); 
  if(mv < criticalThreshold) {
    digitalWrite(ledPin, HIGH);
  }
  else if (mv < warningThreshold) {
    int blinkDelay = map(mv, criticalThreshold, batteryFull, 0, 250);
    flash(blinkDelay);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  delay(1);
}

// function to flash an led with specified on/off time
void flash(int blinkDelay)
{
  digitalWrite(ledPin, HIGH);
  delay(blinkDelay);
  digitalWrite(ledPin, LOW);
  delay(blinkDelay);
}
