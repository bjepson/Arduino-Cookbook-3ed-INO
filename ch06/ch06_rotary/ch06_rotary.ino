/*
 * Read a rotary encoder
 * This simple version polls the encoder pins
 * The position is displayed on the Serial Monitor
 */

const int encoderPinA = 3;
const int encoderPinB = 2;
const int encoderStepsPerRevolution=16;
int angle = 0;

int encoderPos = 0;
bool encoderALast = LOW;  // remembers the previous pin state

void setup()
{
  Serial.begin (9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
}

void loop()
{
  bool encoderA = digitalRead(encoderPinA);

  if ((encoderALast == HIGH) && (encoderA == LOW))
  {
    if (digitalRead(encoderPinB) == LOW)
    {
      encoderPos--;
    }
    else
    {
      encoderPos++;
    }
    angle=(encoderPos % encoderStepsPerRevolution)*360/encoderStepsPerRevolution;
    Serial.print (encoderPos);
    Serial.print (" ");
    Serial.println (angle);
  }

  encoderALast = encoderA;
}
