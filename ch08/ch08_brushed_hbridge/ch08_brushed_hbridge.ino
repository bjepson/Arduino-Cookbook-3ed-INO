/*
 * Brushed_H_Bridge_simple sketch
 * commands from serial port control motor direction
 * + or - set the direction, any other key stops the motor
 */

const int in1Pin = 5;  // H-Bridge input pins
const int in2Pin = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  Serial.println("+ - to set direction, any other key stops motor");
}

void loop()
{
  if ( Serial.available()) {
    char ch = Serial.read();
    if (ch == '+')
    {
      Serial.println("CW");
      digitalWrite(in1Pin,LOW);
      digitalWrite(in2Pin,HIGH);
    }
    else if (ch == '-')
    {
      Serial.println("CCW");
      digitalWrite(in1Pin,HIGH);
      digitalWrite(in2Pin,LOW);
    }
    else if (ch != '\n' && ch != '\r') // ignore cr or lf
    {
      Serial.print("Stop motor");
      digitalWrite(in1Pin,LOW);
      digitalWrite(in2Pin,LOW);
    }
  }
}
