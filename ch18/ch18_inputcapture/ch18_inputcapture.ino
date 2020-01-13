/*
 * InputCapture Sketch
 * uses timer hardware to measure pulses on pin 8 on 168/328
 */

/* some interesting ASCII bit patterns:
 u 01010101
 3 00110011
 ~ 01111110
 @ 01000000
*/ 

const int inputCapturePin = 8;     // input pin fixed to internal Timer
const int ledPin          = LED_BUILTIN;   

const int prescale = 8;            // prescale factor (each tick 0.5 us @16MHz)
const byte prescaleBits = B010;    // see Table 18-1 or Datasheet
// calculate time per counter tick in ns
const long  precision = (1000000/(F_CPU/1000.0)) * prescale;   

const int numberOfEntries  = 64;    // the max number of pulses to measure
const int gateSamplePeriod = 1000;  // the sample period in milliseconds

volatile byte index = 0; // index to the stored readings
volatile byte gate  = 0; // 0 disables capture, 1 enables
volatile unsigned int results[numberOfEntries]; // note this is 16 bit value

/* ICR interrupt vector */
ISR(TIMER1_CAPT_vect)
{
  TCNT1 = 0;                            // reset the counter
  if(gate)
  {
    if( index != 0 || bitRead(TCCR1B ,ICES1) == true)   // wait for rising edge
    {                                     // falling edge was detected
      if(index < numberOfEntries)
      {      
        results[index] = ICR1;              // save the input capture value
        index++;
      } 
    }
  }
  TCCR1B ^= _BV(ICES1);            // toggle bit to trigger on the other edge
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); 
  pinMode(inputCapturePin, INPUT); // ICP pin (digital pin 8 on Arduino) as input

  TCCR1A = 0 ;                    // Normal counting mode
  TCCR1B = prescaleBits ;         // set prescale bits
  TCCR1C = 0;
  bitSet(TCCR1B,ICES1);           // init input capture 
  bitSet(TIFR1,ICF1);             // clear pending 
  bitSet(TIMSK1,ICIE1);           // enable  
   
  Serial.println("pulses are sampled while LED is lit");
  Serial.print( precision);     // report duration of each tick in microseconds
  Serial.println(" microseconds per tick");
}

// this loop prints the duration of pulses detected in the last second
void loop() 
{
  digitalWrite(ledPin, LOW);
  delay(gateSamplePeriod);
  digitalWrite(ledPin, HIGH);  
  index = 0;
  gate = 1; // enable sampling
  delay(gateSamplePeriod);
  gate = 0;  // disable sampling
  if(index > 0)
  {
    Serial.println("Durations in Microseconds are:") ;
    for( byte i=0; i < index; i++)
    {
      long duration;
      duration = results[i] * precision; // pulse duration in nanoseconds
      if(duration > 0) {
        Serial.println(duration / 1000);   // duration in microseconds
        results[i] = 0; // clear value for next reading
      }  
    }
    index = 0;
  }
}
