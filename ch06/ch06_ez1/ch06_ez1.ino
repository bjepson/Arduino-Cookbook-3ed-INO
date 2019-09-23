/*
 * EZ1Rangefinder Distance Sensor
 * prints distance and changes LED flash rate
 * depending on distance from the sensor
 */

const int sensorPin = 5;
const int ledPin    = LED_BUILTIN;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  long value = pulseIn(sensorPin, HIGH) ;
  int cm = value / 58;        // pulse width is 58 microseconds per cm
  Serial.println(cm);

  digitalWrite(ledPin, HIGH);
  delay(cm * 10 ); // each centimeter adds 10 milliseconds delay
  digitalWrite(ledPin, LOW);
  delay( cm * 10);

  delay(20);
}
