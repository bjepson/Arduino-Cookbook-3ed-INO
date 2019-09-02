/*
 * SerialInputGPSHardware sketch
 * Read data from a hardware serial port
 */

#define serial_gps Serial1

void setup()
{
  Serial.begin(9600); // 9600 baud for the built-in serial port
  serial_gps.begin(9600); // initialize the port, most GPS devices 
                          // use 4800 baud
}

void loop()
{
  if (serial_gps.available() > 0) // any character arrived yet?
  {
    char c = serial_gps.read();   // if so, read it from the GPS
    Serial.write(c);              // and echo it to the serial console
  }
}
