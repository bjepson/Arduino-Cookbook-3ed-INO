/*
 * shaken sketch
 * tilt sensor connected to pin 2
 * using the built-in LED
 */

const int tiltSensorPin = 2;
const int ledPin = LED_BUILTIN;
int tiltSensorPreviousValue = 0;
int tiltSensorCurrentValue  = 0;
long lastTimeMoved = 0;
int shakeTime = 100;

void setup()
{
  pinMode (tiltSensorPin, INPUT_PULLUP);
  pinMode (ledPin, OUTPUT);
}

void loop()
{
  tiltSensorCurrentValue = digitalRead(tiltSensorPin);
  if (tiltSensorPreviousValue != tiltSensorCurrentValue)
  {
    lastTimeMoved = millis();
    tiltSensorPreviousValue = tiltSensorCurrentValue;
  }

  if (millis() - lastTimeMoved < shakeTime){
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}
