/*
 * Timer pulse with uTimerLib
 * pulse the onboard LED at a rate set from serial input
 */

#include "uTimerLib.h"

const int pulsePin = LED_BUILTIN;

int period = 100; // period in milliseconds
volatile bool output = HIGH; // the state of the pulse pin

void setup()
{
  pinMode(pulsePin, OUTPUT);
  Serial.begin(9600);
  TimerLib.setInterval_us(flash, period/2 * 1000L);
}

void loop()
{
  if( Serial.available())
  {
    int period = Serial.parseInt();
    if (period)
    {
      Serial.print("Setting period to "); Serial.println(period);
      TimerLib.setInterval_us(flash, period/2 * 1000L);
    }
  }
}

void flash()
{
  digitalWrite(pulsePin, output);
  output = !output;  // invert the output
}
