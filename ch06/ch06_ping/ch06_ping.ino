/* Ping))) Sensor
 * prints distance and changes LED flash rate
 * depending on distance from the Ping))) sensor
 */

const int pingPin = 5;
const int ledPin = LED_BUILTIN; // LED pin

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int cm = ping(pingPin);
  Serial.println(cm);

  digitalWrite(ledPin, HIGH);
  delay(cm * 10); // each centimeter adds 10 milliseconds delay
  digitalWrite(ledPin, LOW);
  delay(cm * 10);
}

// Measure distance and return the result in centimeters
int ping(int pingPin)
{
  long duration; // This will store the measured duration of the pulse

  // Set the pingPin to output.
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW); // Stay low for 2μs to ensure a clean pulse
  delayMicroseconds(2);

  // Send a pulse of 5μs
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // Set the pingPin to input and read the duration of the pulse.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  return duration / 29 / 2;
}
