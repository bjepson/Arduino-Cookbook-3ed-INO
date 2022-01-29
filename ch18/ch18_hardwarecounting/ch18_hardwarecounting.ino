/*
 * HardwareCounting sketch
 *
 * uses pin 5 on 168/328
 */

const int hardwareCounterPin = 5;   // input pin fixed to internal Timer
const int ledPin             = LED_BUILTIN; 

const int samplePeriod = 1000; // the sample period in milliseconds
unsigned int count;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  // hardware counter setup (see ATmega data sheet for details)
  TCCR1A=0;        // reset timer/counter control register A
}  

void loop()
{
  digitalWrite(ledPin, LOW);
  delay(samplePeriod);
  digitalWrite(ledPin, HIGH);  
  // start the counting
  bitSet(TCCR1B, CS12);  // Counter Clock source is external pin
  bitSet(TCCR1B, CS11);  // Clock on rising edge  
  delay(samplePeriod);
  // stop the counting 
  TCCR1B = 0;           
  count = TCNT1;
  TCNT1 = 0;  // reset the hardware counter
  if(count > 0)
     Serial.println(count);
}
