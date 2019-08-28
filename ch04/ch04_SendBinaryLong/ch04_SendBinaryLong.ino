/*
   SendBinary sketch
   Sends a header followed by two random integer values as binary data.
*/

long longValue;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  long longValue = 2147483648;
  int intValue;

  Serial.println("Begin");
  intValue = longValue & 0xFFFF;  // get the value of the lower 16 bits
  Serial.write(lowByte(intValue));
  Serial.write(highByte(intValue));

  intValue = longValue >> 16;  // get the value of the higher 16 bits
  Serial.write(lowByte(intValue));
  Serial.write(highByte(intValue));
  Serial.println("Done");
}

void loop()
{
  Serial.print('H'); // send a header character

  // send two random long values
  long longValue = random(2147483648); // generate a random number between 0 and 2147483648
  sendBinary(longValue);

  longValue = random(2147483648); // generate a random number between 0 and 2147483648
  sendBinary(longValue);

  delay(1000);
}

// function to send the given integer value to the serial port
void sendBinary(int value)
{
  // send the two bytes that comprise a two byte (16 bit) integer
  Serial.write(lowByte(value));  // send the low byte
  Serial.write(highByte(value)); // send the high byte
}

// function to send the given long integer value to the serial port
void sendBinary(long value)
{
  // first send the low 16 bit integer value
  int temp = value & 0xFFFF;  // get the value of the lower 16 bits
  sendBinary(temp);
  // then send the higher 16 bit integer value:
  temp = value >> 16;  // get the value of the higher 16 bits
  sendBinary(temp);
}
