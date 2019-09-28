/* piezo sketch
   lights an LED when the Piezo is tapped
*/

const int sensorPin = A0;  // the analog pin connected to the sensor
const int ledPin    = LED_BUILTIN;     // pin connected to LED
const int THRESHOLD = 155;


void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(sensorPin);
  if (val >= THRESHOLD)
  {
    Serial.println(val);
    digitalWrite(ledPin, HIGH);
    delay(100);  // to make the LED visible
  }
  else
    digitalWrite(ledPin, LOW);
}
