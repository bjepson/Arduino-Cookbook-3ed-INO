/*
  XBeeActuateSeries1
  Activate a digital pin on another XBee.
 */

const int xbeePin = 2;

void setup() {
  pinMode(xbeePin, OUTPUT);
}

void loop()
{
  digitalWrite(xbeePin, HIGH);
  delay(2000);
  digitalWrite(xbeePin, LOW);
  delay(2000);
}
