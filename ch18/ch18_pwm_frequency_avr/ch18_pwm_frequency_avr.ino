/*
 * Set PWM Frequency sketch.
 * Frequency is set via the serial port.
 * A digit from 1-7 followed by a, b, or c Timer1, 2, 3 adjusts frequency
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

void loop()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if(ch >= '1' && ch <= '7') // is ch a valid digit?
    {
      prescale = ch - '0';
    }
    else if(ch == 'a' && prescale)  // timer 0;
    {
      TCCR0B = (TCCR0B & mask)  | prescale;
    }
    else if(ch == 'b' && prescale)  // timer 1;
    {
      TCCR1B = (TCCR1B & mask)  | prescale;
    }
    else if(ch == 'c' && prescale)  // timer 2;
    {
      TCCR2B = (TCCR2B & mask)  | prescale;
    }
  }
}
