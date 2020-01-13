/*
 * Interrupts sketch
 * see #responding_to_an_infrared_remote_cont for connection diagram
 */

const int pin = 2; // pin the receiver is connected to
const int numberOfEntries = 32; // set this number to any convenient value        

volatile unsigned long microseconds;
volatile byte idx = 0;
volatile unsigned long results[numberOfEntries];

void setup()
{
  pinMode(pin, INPUT_PULLUP);
  Serial.begin(9600);
  // Use the pin's interrupt to monitor for changes
  attachInterrupt(digitalPinToInterrupt(pin), analyze, CHANGE);
  results[0]=0;
}

void loop()
{
  if(idx >= numberOfEntries)
  {
    Serial.println("Durations in Microseconds are:") ;
    for( byte i=0; i < numberOfEntries; i++)
    {
      Serial.print(i); Serial.print(": ");
      Serial.println(results[i]);
    }
    idx = 0; // start analyzing again
  }
  delay(1000);
}

void analyze()
{
  if(idx < numberOfEntries)
  {
    if(idx > 0)
    {
      results[idx] = micros() - microseconds;
    }
    idx = idx + 1;
  }
  microseconds = micros();
}
