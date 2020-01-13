/*
 * Sampling rate sketch
 * Increases the sampling rate for analogRead
 */
const int sensorPin = 0;             // pin the receiver is connected to
const int numberOfEntries = 100;

unsigned long microseconds;
unsigned long duration;

int results[numberOfEntries];

void setup()
{
  Serial.begin(9600);
  while(!Serial); // Needed for Leonardo

  // standard analogRead performance (prescale = 128)
  microseconds = micros();
  for(int i = 0; i < numberOfEntries; i++)
  {
    results[i] = analogRead(sensorPin);
  }
  duration = micros() - microseconds;
  Serial.print(numberOfEntries);
  Serial.print(" readings took ");
  Serial.println(duration);

  // running with high speed clock (set prescale to 16)
  bitClear(ADCSRA,ADPS0);
  bitClear(ADCSRA,ADPS1);
  bitSet(ADCSRA,ADPS2);
  microseconds = micros();
  for(int i = 0; i < numberOfEntries; i++)
  {
    results[i] = analogRead(sensorPin);
  }
  duration = micros() - microseconds;
  Serial.print(numberOfEntries);
  Serial.print(" readings took ");
  Serial.println(duration);
}

void loop()
{
}
