/*
 * Brushed_H_Bridge sketch with speed control
 * commands from serial port control motor speed and direction
 * digits '0' through '9' are valid where '0' is off, '9' is max speed
 * + or - set the direction
 */

const int enPin  = 5;  // H-Bridge enable pin
const int in1Pin = 7;  // H-Bridge input pins
const int in2Pin = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  Serial.println("Speed (0-9) or + - to set direction");
}

void loop()
{
  if ( Serial.available()) 
  {
    char ch = Serial.read();

    if(isDigit(ch)) // is ch a number?
    {
      int speed = map(ch, '0', '9', 0, 255);
      analogWrite(enPin, speed);
      Serial.println(speed);
    }
    else if (ch == '+')
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
      Serial.print("Unexpected character ");
      Serial.println(ch);
    }
  }
}
