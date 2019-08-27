/*
 * SerialReceiveMultipleFields sketch
 * This code expects a message in the format: H,12,345,678
 * This code requires a newline character to indicate the end of the data
 * Set the serial monitor to send newline characters
 */

const int NUMBER_OF_FIELDS = 3; // how many comma separated fields we expect
int values[NUMBER_OF_FIELDS];   // array holding values for all the fields

void setup()
{
  Serial.begin(9600); // Initialize serial port to send and receive at 9600 baud
}

void loop()
{
  if ( Serial.available())
  {
    if (Serial.read() == 'H') {

      // Read the values
      for (int i = 0; i < NUMBER_OF_FIELDS; i++)
      {
        values[i] = Serial.parseInt();
      }

      // Display the values in comma-separated format
      Serial.print(values[0]); // First value

      // Print the rest of the values with a leading comma
      for (int i = 1; i < NUMBER_OF_FIELDS; i++) 
      {
        Serial.print(","); Serial.print(values[i]); 
      }
      Serial.println();
    }
  }
}
