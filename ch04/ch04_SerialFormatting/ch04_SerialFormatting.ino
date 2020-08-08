#include <Streaming.h>

/*
  SerialFormatting
  Print values in various formats to the serial port
*/


char chrValue  = 65;  // these are the starting values to print
byte byteValue = 65;
int intValue   = 65;
float floatValue = 65.0;

void setup()
{
  while (!Serial); // Wait until serial port's open on Leonardo and SAMD boards
  Serial.begin(9600);
  int t = 5;
  int s = 17;
  int d = 120;
  Serial.print("At ");
  Serial.print(t);
  Serial.print(" seconds: speed = ");
  Serial.print(s);
  Serial.print(", distance = ");
  Serial.println(d);

  Serial.print("At "); Serial.print(t); Serial.print(" seconds, speed = ");
  Serial.print(s); Serial.print(", distance = "); Serial.println(d);
  Serial << "At " << t << " seconds, speed = " << s << ", distance = " << d << endl;
//  char buf[100];
//  sprintf(buf, "At %d seconds, speed = %d, distance = %d", t, s, d);
//  Serial.println(buf);
//  snprintf(buf, sizeof (buf) / sizeof (buf[0]),
//           "At %d seconds, speed = %d, distance = %d", t, s, d);
//  Serial.println(buf);

//  long buf2[100];
//  Serial.println(sizeof(buf2));
//  Serial.println(sizeof (buf2) / sizeof (buf2[0]));
}

void loop()
{
  Serial.print("chrValue:   ");
  Serial.print(chrValue); Serial.print(" ");
  Serial.write(chrValue); Serial.print(" ");
  Serial.print(chrValue, DEC);
  Serial.println();

  Serial.print("byteValue:  ");
  Serial.print(byteValue); Serial.print(" ");
  Serial.write(byteValue); Serial.print(" ");
  Serial.print(byteValue, DEC);
  Serial.println();

  Serial.print("intValue:   ");
  Serial.print(intValue); Serial.print(" ");
  Serial.print(intValue, DEC); Serial.print(" ");
  Serial.print(intValue, HEX); Serial.print(" ");
  Serial.print(intValue, OCT); Serial.print(" ");
  Serial.print(intValue, BIN);
  Serial.println();

  Serial.print("floatValue: ");
  Serial.println(floatValue);
  Serial.println();

  delay(1000); // delay a second between numbers
  chrValue++;  // to the next value
  byteValue++;
  intValue++;
  floatValue += 1;
}
