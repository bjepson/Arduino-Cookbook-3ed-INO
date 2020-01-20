/*
 * XBeeAnalogReceive Series 2 sketch
 * Read an analog value from an XBee API frame and set the brightness
 * of an LED accordingly.
 */

// Uncomment only one of the following
#define MYSERIAL Serial // Uno, Nano, and other AVR boards
//#define MYSERIAL Serial1 // Nano Every, Uno WiFi R2, Leonardo, and ARM boards

#define MIN_CHUNK 24
#define OFFSET 18

const int ledPin = A5; // Analog pin 5

void setup() 
{
  MYSERIAL.begin(9600);
}

void loop() 
{
  if (MYSERIAL.available() >= MIN_CHUNK) // Wait until we have a mouthful of data
  { 
    if (MYSERIAL.read() == 0x7E) // Start delimiter of a frame
     { 
      // Skip over the bytes in the API frame we don't care about
      for (int i = 0; i < OFFSET; i++) 
      {
        MYSERIAL.read();
      }

      // The next two bytes are the high and low bytes of the sensor reading
      int analogHigh = MYSERIAL.read();
      int analogLow = MYSERIAL.read();
      int analogValue = analogLow + (analogHigh * 256);

      // Scale the brightness to the Arduino PWM range
      int brightness = map(analogValue, 0, 1023, 0, 255);

      // Light the LED
      analogWrite(ledPin, brightness);
    }
  }
}
