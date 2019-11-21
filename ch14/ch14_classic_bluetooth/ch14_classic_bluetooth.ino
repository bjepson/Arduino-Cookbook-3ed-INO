/*
 * Classic Bluetooth sketch
 * Use SoftwareSerial or Serial1 to talk to BlueSMiRF module
 * note pairing code is 1234
 */

//#define USESERIAL1 // Uncomment this if you're on an ARM or Leonardo
#ifdef USESERIAL1
  #define BTSERIAL Serial1
#else
  #include <SoftwareSerial.h>
  const int rxpin = 2;  // pin used to receive
  const int txpin = 3;  // pin used to send to
  SoftwareSerial mySerial(rxpin, txpin); // new serial port on given pins
  #define BTSERIAL mySerial // software serial
#endif

void setup()
{
  Serial.begin(9600);  
  BTSERIAL.begin(9600); // initialize the software serial port
  Serial.println("Serial ready");
  BTSERIAL.println("Bluetooth ready");  
}

void loop()
{
  if (BTSERIAL.available())
  {
    char c = (char)BTSERIAL.read();
    Serial.write(c);
  }
  if (Serial.available())
  {
    char c = (char)Serial.read();
    BTSERIAL.write(c);
  }
}
