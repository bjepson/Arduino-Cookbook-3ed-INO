/*
  XBeeAnalogReceive Series 2 sketch
  Read an analog value from an XBee API frame and set the brightness
  of an LED accordingly.
 */

#define MYSERIAL Serial // Uno, Nano, and other ATmega328 boards
#define MYSERIAL Serial1 // Uncomment for Leonardo and most ARM-based boards

const int ledPin = 5;

void setup() 
{
  MYSERIAL.begin(9600);
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  if (MYSERIAL.available() >= 24) // Wait until we have a mouthful of data
  { 
    if (MYSERIAL.read() == 0x7E) // Start delimiter of a frame
     { 
      // Skip over the bytes in the API frame we don't care about
      for (int i = 0; i < 20; i++) 
      {
        MYSERIAL.read();
      }

      // The next two bytes are the high and low bytes of the sensor reading
      int analogHigh = MYSERIAL.read();
      int analogLow = MYSERIAL.read();
      int analogValue = analogLow + (analogHigh * 256);
Serial.print(analogHigh,HEX);
Serial.print(analogLow,HEX);
      // Scale the brightness to the Arduino PWM range
      int brightness = map(analogValue, 0, 1023, 0, 255);

      // Light the LED
      analogWrite(ledPin, brightness);
      Serial.println();
    }
  }
}
