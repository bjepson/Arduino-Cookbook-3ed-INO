/*
   EZ1Rangefinder Distance Sensor
   prints distance and changes LED flash rate
   depending on distance from the sensor
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
  int value = analogRead(A0);
  float mv = (value / 1024.0) * 5000 ;
  float inches  =  mv / 9.8; // 9.8mv per inch per datasheet
  float cm = inches * 2.54;
  Serial.print("in: "); Serial.println(inches);
  Serial.print("cm: "); Serial.println(cm);

  digitalWrite(ledPin, HIGH);
  delay(cm * 10 ); // each centimeter adds 10 milliseconds delay
  digitalWrite(ledPin, LOW);
  delay( cm * 10);

  delay(20);
}
