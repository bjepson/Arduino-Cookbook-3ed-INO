/*
 * Stepper_Easystepper sketch
 * stepper is controlled from the serial port.
 * a numeric value followed by '+' or '-' steps the motor
 * a numeric value followed by 's' changes the speed
 */

const int dirPin  = 2;
const int stepPin = 3;
const int enPin   = 4;

// use the following for speed given in RPM
int speed = 60;    // desired speed in RPM
int stepsPerRevolution = 200;  // this line sets steps for one revolution
int steps = 0;      // the number of steps to make
long last_step = millis();
long timeout = 30 * 1000; // turn off the motor after 30 secs of inactivity


void setup()
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (millis() > last_step + timeout)
  {
    digitalWrite(enPin,HIGH); // Turn off the motor
  }  

  if ( Serial.available()) 
  {
    char ch = Serial.read();

    if(isDigit(ch)) // is ch a number?
    {
      steps = steps * 10 + ch - '0'; // yes, accumulate the value
    }
    else if(ch == '+')
    {
      step(steps);
      steps = 0;
    }
    else if(ch == '-')
    {
      step(-steps);
      steps = 0;
    }
    else if(ch == 's')
    {
      speed = steps;
      Serial.print("Setting speed to "); Serial.println(steps);
      steps = 0;
    }
  }
}

void step(int steps)
{
  int stepDelay = 60L * 1000L / stepsPerRevolution / speed; // speed as RPM
  int stepsLeft;

  digitalWrite(enPin,LOW); // Enable the motor
  last_step = millis();

  // determine direction based on whether steps_to_mode is + or -
  if (steps > 0)
  {
    digitalWrite(dirPin, HIGH);
    stepsLeft = steps;
  }
  if (steps < 0)
  {
    digitalWrite(dirPin, LOW);
    stepsLeft = -steps;
  }
  // decrement the number of steps, moving one step each time
  while(stepsLeft > 0)
  {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(1);
    digitalWrite(stepPin,LOW);
    delay(stepDelay);
    stepsLeft--; // decrement the steps left
  }
}
