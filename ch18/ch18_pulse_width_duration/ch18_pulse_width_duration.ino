/*
 * Pulse width duration sketch
 * Set period and width of pulses
 */

#include <TimerOne.h>

const int outPin = 9; // pin; use 3-4 on Teensy 3.x, 11-13 on Arduino Mega

long period = 40; // 40-microsecond period (25 KHz)
long width  = 20; // 20-microsecond width (50% duty cycle)

void setup()
{
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
  Timer1.initialize(period); // initialize timer1, 10000 microseconds
  int dutyCycle = map(width, 0,period, 0,1023);
  Timer1.pwm(outPin, dutyCycle); // PWM on output pin
}

void loop()
{
}
