/*
 * LedBrightness sketch
 * controls the brightness of LEDs on analog output ports
 */

const int firstLed   = 3; // specify the pin for each of the LEDs
const int secondLed  = 5;
const int thirdLed   = 6;

int brightness = 0;
int increment  = 1;
#define MAX_BRIGHTNESS 128

void setup()
{
  // pins driven by analogWrite do not need to be declared as outputs
}

void loop()
{
  if(brightness > MAX_BRIGHTNESS)
  {
    increment = -1; // count down after reaching MAX_BRIGHTNESS
  }
  else if(brightness < 1)
  {
    increment =  1; // count up after dropping back down to 0
  }
  brightness = brightness + increment; // increment (or decrement sign is minus)

  // write the brightness value to the LEDs
  analogWrite(firstLed, brightness);
  analogWrite(secondLed, brightness);
  analogWrite(thirdLed, brightness );

  delay(25); // 10ms for each step change means 2.55 secs to fade up or down
}
