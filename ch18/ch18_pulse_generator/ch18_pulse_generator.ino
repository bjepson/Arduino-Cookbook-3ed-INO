/*
 * Configurable Pulse Generator sketch
 */
#include <TimerOne.h>

const char SET_PERIOD_HEADER      = 'p';
const char SET_FREQUENCY_HEADER   = 'f';
const char SET_PULSE_WIDTH_HEADER = 'w';
const char SET_DUTY_CYCLE_HEADER  = 'c';

const int outPin = 9; // pin; use 3-4 on Teensy 3.x, 11-13 on Arduino Mega

long period = 40; // 40-microsecond period (25 KHz)
int duty = 512;   // duty as a range from 0 to 1023, 512 is 50% duty cycle

void setup()
{
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
  Timer1.initialize(period); // initialize timer1, 1000 microseconds
  Timer1.pwm(outPin, duty); // PWM on output pin
  instructions();
}

void loop()
{
  processSerial();
}

void processSerial()
{
  static long val = 0;

  if (Serial.available())
  {
    val = Serial.parseInt(); // Find the first number
    if (val)
    {
      char ch = Serial.read();
      switch(ch)
      {
        case SET_PERIOD_HEADER:
          period = val;
          Serial.print("Setting period to ");
          Serial.println(period);
          Timer1.setPeriod(period);
          Timer1.pwm(outPin, duty);
          show();
          break;
        case SET_FREQUENCY_HEADER:
          if(val > 0)
          {
            Serial.print("Setting frequency to ");
            Serial.println(val);
            period = 1000000 / val;
            Timer1.setPeriod(period);
            Timer1.pwm(outPin, duty);
          }
          show();
          break;
        case SET_PULSE_WIDTH_HEADER:
          if( val < period && val > 0) {
            long width = val;
            Serial.print("Setting Pulse width to ");
            Serial.println(width);
            duty = map(width, 0,period, 0,1023);
            Timer1.pwm(outPin, duty);
           }
          else
             Serial.println("Pulse width too long for current period");
          show();
          break;
        case SET_DUTY_CYCLE_HEADER:
          if( val >0 && val < 100)
          {
            Serial.print("Setting Duty Cycle to ");
            Serial.println(val);
            duty = map(val, 0,99, 0,1023);
            Timer1.pwm(outPin, duty);
            show();
          }
      }
    }
  }
}

void show()
{
  Serial.print("The period is ");
  Serial.println(period);
  Serial.print("Duty cycle is ");
  Serial.print(map(duty, 0,1023, 0,99));      
  Serial.println("%");
  Serial.println();
  instructions();
}

void instructions()
{
  Serial.println("Send values followed by one of the following tags:");
  Serial.println(" p - sets period in microseconds");
  Serial.println(" f - sets frequency in Hz");
  Serial.println(" w - sets pulse width in microseconds");
  Serial.println(" c - sets duty cycle in %");
  Serial.println("\n(duty cycle can have one decimal place)\n");
}
