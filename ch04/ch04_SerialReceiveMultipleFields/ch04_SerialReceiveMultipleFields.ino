/*
 * SerialReceiveMultipleFields sketch
 * This code expects a message in the format: H,12,345,678
 * This code requires a newline character to indicate the end of the data
 * Set the serial monitor to send newline characters
 */

const int NUMBER_OF_FIELDS = 3; // how many comma separated fields we expect
int fieldIndex = 0;            // the current field being received
int values[NUMBER_OF_FIELDS];   // array holding values for all the fields

void setup()
{
  Serial.begin(9600); // Initialize serial port to send and receive at 9600 baud
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if ( Serial.available())
  {
    if (Serial.read() == 'H') {
      for (int i = 0; i < NUMBER_OF_FIELDS; i++)
      {
        values[i] = Serial.parseInt();
        Serial.print(values[i]); Serial.print(",");
      }
      Serial.println();

      for (int i = 0; i < NUMBER_OF_FIELDS; i++)
      {
        blink(values[i]);        
      }
    }
  }
}

void blink(int times)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(125);
    digitalWrite(LED_BUILTIN, LOW);
    delay(125);
  }
  delay(250);
  
}
