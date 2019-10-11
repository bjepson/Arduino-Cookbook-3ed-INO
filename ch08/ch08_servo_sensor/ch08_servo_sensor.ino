/*
 * Servo With Sensor sketch
 * Control a servo with a sensor.
 */

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = A0; // analog pin used to connect the potentiometer
int val;         // variable to read the value from the analog pin

void setup()
{
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop()
{
  val = analogRead(potpin);            // reads the value of the potentiometer
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo
  myservo.write(val);                  // sets position to the scaled value
  delay(15);                           // waits for the servo to get there
}
