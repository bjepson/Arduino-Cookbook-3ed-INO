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

long runningAverage = 0;      // the running average of calculated values
const int averagedOver = 3;   // how quickly new values affect running average
                              // bigger numbers mean slower

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
    runningAverage=(((averagedOver-1)*runningAverage)+encoderPos)/averagedOver;
    Serial.println(runningAverage);
  }

  encoderALast = encoderA;
}
