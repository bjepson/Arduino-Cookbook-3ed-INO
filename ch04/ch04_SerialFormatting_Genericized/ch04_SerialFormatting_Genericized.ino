/*
  Serial11Formatting
  Print values in various formats to the Serial11 port
*/
char chrValue = 65;  // these are the starting values to print
byte byteValue = 65;
int intValue  = 65;
float floatValue = 65.0;
char c1 = 4;
char c2 = 210;

#ifdef TEENSYDUINO
usb_serial_class &MySerial = Serial;
#else
HardwareSerial &MySerial = Serial;
#endif

void setup()
{
  MySerial.begin(9600);
  while (!Serial);
}

void loop()
{
  MySerial.print("chrValue: ");
  MySerial.print(chrValue); MySerial.print(" ");
  MySerial.write(chrValue); MySerial.print(" ");
  MySerial.print(chrValue, DEC);
  MySerial.println();

  MySerial.print("byteValue: ");
  MySerial.print(byteValue); MySerial.print(" ");
  MySerial.write(byteValue); MySerial.print(" ");
  MySerial.print(byteValue, DEC);
  MySerial.println();

  MySerial.print("intValue: ");
  MySerial.print(intValue); MySerial.print(" ");
  MySerial.print(intValue, DEC); MySerial.print(" ");
  MySerial.print(intValue, HEX); MySerial.print(" ");
  MySerial.print(intValue, OCT); MySerial.print(" ");
  MySerial.print(intValue, BIN);
  MySerial.println();

  MySerial.print("floatValue: ");
  MySerial.println(floatValue);
  MySerial.println();

  delay(1000); // delay a second between numbers
  chrValue++;  // to the next value
  byteValue++;
  intValue++;
  floatValue += 1;
}
