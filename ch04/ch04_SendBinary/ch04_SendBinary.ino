/*
 * SendBinary sketch
 * Sends a header followed by two random integer values as binary data.
*/

short intValue; // short integer value (16 bits on all boards)

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print('H'); // send a header character

  // send a random integer
  intValue = random(599); // generate a random number between 0 and 599
  // send the two bytes that comprise that integer
  Serial.write(lowByte(intValue));  // send the low byte
  Serial.write(highByte(intValue)); // send the high byte

  // send another random integer
  intValue = random(599); // generate a random number between 0 and 599
  // send the two bytes that comprise that integer
  Serial.write(lowByte(intValue));  // send the low byte
  Serial.write(highByte(intValue)); // send the high byte

  delay(1000);
}
