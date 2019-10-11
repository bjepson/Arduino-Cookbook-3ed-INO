/*
 * Continuous rotation
 */
#include <Servo.h>

Servo myservoLeft;   // create servo object to control a servo
Servo myservoRight;  // create servo object to control a servo

int angle = 0;    // variable to store the servo position

void setup()
{
  myservoLeft.attach(9);   // attaches left servo on pin 9 to servo object
  myservoRight.attach(10); // attaches right servo on pin 10 to servo object
}

void loop()
{
  for(angle = 90; angle < 180; angle += 1)  // goes from 90 to 180 degrees
  {                                         // in steps of 1 degree.
                                            // 90  degrees is stopped.
                                          
    myservoLeft.write(angle);        // rotate servo at speed given by 'angle'
    myservoRight.write(180-angle);   // go in the opposite direction

    delay(20);                       // waits 20ms between servo commands
  }
  for(angle = 180; angle >= 90; angle -= 1) // goes from 180 to 90 degrees
  {
    myservoLeft.write(angle);        // rotate at a speed given by 'angle'
    myservoRight.write(180-angle);   // other servo goes in opposite direction
  }
}
