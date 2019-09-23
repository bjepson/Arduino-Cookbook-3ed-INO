/* HC-SR04 Sensor
 * prints distance and changes LED flash rate
 * depending on distance from the HC-SR04 sensor
 */

const int trigPin = 5; // Pin to send the ping from
const int echoPin = 6; // Pin to read the response from
const int ledPin  = LED_BUILTIN; // LED pin

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  int cm = calculateDistance(trigPin);
  Serial.println(cm);

  digitalWrite(ledPin, HIGH);
  delay(cm * 10); // each centimeter adds 10 milliseconds delay
  digitalWrite(ledPin, LOW);
  delay(cm * 10);
}

int calculateDistance(int trigPin)
{
  long duration; // This will store the measured duration of the pulse

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);  // Stay low for 2μs to ensure a clean pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Send a pulse of 10μs to ensure a clean pulse
  digitalWrite(trigPin, LOW);

  // Read the duration of the response pulse
  duration = pulseIn(echoPin, HIGH);

  // convert time into distance
  return duration / 29 / 2;
}
