/*
 * SendBinaryFields
 * Sends digital and analog pin values as binary data
 */

const char HEADER = 'H';  // a single character header to indicate
                          // the start of a message

void setup()
{
  Serial.begin(9600);
  for(int i=2; i <= 13; i++)
  {
    pinMode(i, INPUT_PULLUP);  // set pins 2 through 13 to inputs (with pullups)
  }
}

void loop()
{
  Serial.write(HEADER); // send the header
  // put the bit values of the pins into an integer
  int values = 0;
  int bit = 0;

  for(int i=2; i <= 13; i++)
  {
    bitWrite(values, bit, digitalRead(i));  // set the bit to 0 or 1 depending
                                            // on value of the given pin
    bit = bit + 1;                          // increment to the next bit
  }
  sendBinary(values); // send the integer

  for(int i=0; i < 6; i++)
  {
    values = analogRead(i);
    sendBinary(values); // send the integer
  }
  delay(1000); //send every second
}

// function to send the given integer value to the serial port
void sendBinary(int value)
{
  // send the two bytes that comprise an integer
  Serial.write(lowByte(value));  // send the low byte
  Serial.write(highByte(value)); // send the high byte
}
