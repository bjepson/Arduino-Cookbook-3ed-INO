/*
 * Set PWM Frequency sketch.
 * Frequency is set via the serial port.
 * A digit from 1-7 followed by a, b, or c Timer0, 1, 2 adjusts frequency
 */
const byte mask = B11111000; // mask bits that are not prescale values
int prescale = 0;

void setup()
{
  Serial.begin(9600);
  analogWrite(3,128);
  analogWrite(5,128);
  analogWrite(6,128);
  analogWrite(9,128);
  analogWrite(10,128);
  analogWrite(11,128);
}

long last_change = millis();
long wait_delay = 20;
int direction = 1;
int val = 0;

void loop()
{
  if (millis() > last_change + wait_delay) {
    if (val >= 255)
      direction = -1;
    if (val <= 0)
      direction = 1;
      Serial.println(val);
    val += direction; 
    analogWrite(9, val);
    last_change = millis();
  }
  if ( Serial.available())
  {
    char ch = Serial.read();
    if(ch >= '0' && ch <= '9')              // is ch a number?
    {
      prescale = ch - '0';
    }
    else if(ch == 'a')  // timer 0;
    {
      TCCR0B = (TCCR0B & mask)  | prescale;
    }
    else if(ch == 'b')  // timer 1;
    {
      TCCR1B = (TCCR1B & mask)  | prescale;
    }
    else if(ch == 'c')  // timer 2;
    {
      TCCR2B = (TCCR2B & mask)  | prescale;
    }
  }
}
