/*
 * XBeeAnalogReceive Series 1 or XBee 3 Sketch
 * Read an analog value from an XBee API frame and set the brightness
 * of an LED accordingly.
 */

// Uncomment only one of the following
#define MYSERIAL Serial // Uno, Nano, and other AVR boards
//#define MYSERIAL Serial1 // Nano Every, Uno WiFi R2, Leonardo, and ARM boards

// Use these settings for XBee 3:
#define MIN_CHUNK 21
#define OFFSET 18

// Use these settings for XBee Series 1:
//#define MIN_CHUNK 14
//#define OFFSET 10

const int ledPin = A5;

void setup() 
{
  MYSERIAL.begin(9600);
  delay(1000);
  configureRadio(); // check the return value if you need error handling
}

bool configureRadio() 
{
  // put the radio in command mode:
  MYSERIAL.flush();
  MYSERIAL.print("+++");
  delay(100);

  String ok_response = "OK\r"; // the response we expect.

  // Read the text of the response into the response variable
  String response = String("");
  while (response.length() < ok_response.length()) 
  {
    if (MYSERIAL.available() > 0) 
    {
      response += (char) MYSERIAL.read();
    }
  }

  // If we got the right response, configure the radio and return true.
  if (response.equals(ok_response)) 
  {
    MYSERIAL.print("ATAP1\r"); // Enter API mode
    delay(100);
    MYSERIAL.print("ATCN\r");  // back to data mode
    return true;
  } 
  else 
  {
    return false; // This indicates the response was incorrect.
  }
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
