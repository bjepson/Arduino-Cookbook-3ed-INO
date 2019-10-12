/*
 * Brushed_H_Bridge_Direction sketch for Adafruit Motor shield
 * uses photo sensors to control motor direction
 * robot moves in the direction of a light 
 */

#include <Wire.h>
#include <Adafruit_MotorShield.h> // Adafruit motor shield library

// Create an object for the shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

const int MIN_PWM        = 64;  // this can range from 0 to MAX_PWM
const int MAX_PWM        = 128; // this can range from around 50 to 255
const int leftSensorPin  = A0;  // analog pins with sensors
const int rightSensorPin = A1;

int sensorThreshold = 0;  // must be more light than this on sensors to move

void setup()
{
  AFMS.begin();  // create with the default frequency 1.6KHz
}

void loop()
{
  int leftVal  = analogRead(leftSensorPin);
  int rightVal = analogRead(rightSensorPin);
 
  if(sensorThreshold == 0) // have the sensors been calibrated?
  {  
    // if not, calibrate sensors to something above the ambient average  
    sensorThreshold = ((leftVal + rightVal) / 2) + 100 ;  
  }   
 
  if( leftVal > sensorThreshold || rightVal > sensorThreshold)  
  {   
    // if there is adequate light to move ahead
    setSpeed(rightMotor, map(rightVal,0,1023, MIN_PWM, MAX_PWM));
    setSpeed(leftMotor,  map(leftVal ,0,1023, MIN_PWM, MAX_PWM));
  }
}

void setSpeed(Adafruit_DCMotor *motor, int speed )
{
  if(speed < 0)
  {
    motor->run(BACKWARD);
    speed = -speed;
  }
  else
  {
    motor->run(FORWARD);
  }
  motor->setSpeed(speed);
}
