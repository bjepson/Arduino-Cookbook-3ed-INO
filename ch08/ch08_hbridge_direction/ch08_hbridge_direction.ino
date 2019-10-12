/*
 * Brushed_H_Bridge_Direction sketch
 * uses photo sensors to control motor direction
 * robot moves in the direction of a light
 */

int leftPins[]  = {5,7,4};  // on pin for PWM, two pins for motor direction
int rightPins[] = {6,3,2};

const int MIN_PWM        = 64;  // this can range from 0 to MAX_PWM;
const int MAX_PWM        = 255; // this can range from around 50 to 255;
const int leftSensorPin  = A0;  // analog pins with sensors
const int rightSensorPin = A1;

int sensorThreshold = 0; // must have this much light on a sensor to move

void setup()
{
  for(int i=1; i < 3; i++)
  {
    pinMode(leftPins[i], OUTPUT);
    pinMode(rightPins[i], OUTPUT);
  }
  Serial.begin(9600);
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
    setSpeed(leftPins,  map(leftVal ,0,1023, MIN_PWM, MAX_PWM));
    Serial.print("Right:"); Serial.println(map(rightVal,0,1023, MIN_PWM, MAX_PWM));
    Serial.print("Left:"); Serial.println(map(leftVal ,0,1023, MIN_PWM, MAX_PWM));
  }
}

void setSpeed(int pins[], int speed )
{
  if(speed < 0)
  {
    digitalWrite(pins[1],HIGH);
    digitalWrite(pins[2],LOW);
    speed = -speed;
  }
  else
  {
    digitalWrite(pins[1],LOW);
    digitalWrite(pins[2],HIGH);
  }
  analogWrite(pins[0], speed);
}
