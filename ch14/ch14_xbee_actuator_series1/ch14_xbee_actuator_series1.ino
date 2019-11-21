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
  delay(3000);
  digitalWrite(xbeePin, LOW);
  delay(3000);
}
