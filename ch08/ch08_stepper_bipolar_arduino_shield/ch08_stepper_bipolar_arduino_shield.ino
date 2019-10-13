/*
   Stepper_bipolar sketch for Arduino motor shield
   stepper is controlled from the serial port.
   a numeric value followed by '+' or '-' steps the motor
*/

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 64

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 12, 13);

int steps = 0;

void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);   // enable A

  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);   // enable B
  
  stepper.setSpeed(60);   // set the speed of the motor to 30 rpm

  Serial.begin(9600);

}

void loop()
{
  if ( Serial.available())
  {
    char ch = Serial.read();

    if (isDigit(ch)) // is ch a number?
    {
      steps = steps * 10 + ch - '0'; // yes, accumulate the value
    }
    else if (ch == '+')
    {
      digitalWrite(3, HIGH);   // enable A
      digitalWrite(11, HIGH);   // enable B

      Serial.print("Moving +"); Serial.println(steps);
      stepper.step(steps);
      steps = 0;
    }
    else if (ch == '-')
    {
      digitalWrite(3, HIGH);   // enable A
      digitalWrite(11, HIGH);   // enable B
      stepper.step(steps * -1);
      steps = 0;
    }
  }

  digitalWrite(3, LOW);   // disable A
  digitalWrite(11, LOW);   // disable B

}
