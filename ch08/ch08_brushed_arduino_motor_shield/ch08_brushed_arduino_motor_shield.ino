/*
 * Brushed_H_Bridge_Direction sketch for Ardumotor shield
 * uses photo sensors to control motor direction
 * robot moves in the direction of a light
 */

int leftPins[]  = {3,12};   // one pin for PWM, one pin for motor direction
int rightPins[] = {11,13};

const int MIN_PWM        = 128;  // this can range from 0 to MAX_PWM;
const int MAX_PWM        = 255; // this can range from around 50 to 255;
const int leftSensorPin  = A2;  // analog pins with sensors
const int rightSensorPin = A3;

int sensorThreshold = 0; // must have this much light on a sensor to move

void setup()
{
  pinMode(leftPins[1], OUTPUT);
  pinMode(rightPins[1], OUTPUT);
}

void loop()
{
  int leftVal = analogRead(leftSensorPin);
  int rightVal = analogRead(rightSensorPin);
  if(sensorThreshold == 0) // have the sensors been calibrated?
  {  
     // if not, calibrate sensors to something above the ambient average  
     sensorThreshold = ((leftVal + rightVal) / 2) + 100 ; 
  }
  
  if( leftVal > sensorThreshold || rightVal > sensorThreshold)
  {
    // if there is adequate light to move ahead
    setSpeed(rightPins, map(rightVal,0,1023, MIN_PWM, MAX_PWM));
    setSpeed(leftPins,  map(leftVal, 0,1023, MIN_PWM, MAX_PWM));
  }
}

void setSpeed(int pins[], int speed )
{
  if(speed < 0)
  {
    digitalWrite(pins[1], HIGH);
    speed = -speed;
  }
  else
  {
    digitalWrite(pins[1], LOW);
  }
  analogWrite(pins[0], speed);
}
