/*
 * matrixMpx sketch
 *
 * Sequence LEDs starting from first column and row until all LEDS are lit
 * Multiplexing is used to control 64 LEDs with 16 pins
 */

const int columnPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int rowPins[]    = {10,11,12,A1,A2,A3,A4,A5};

int pixel       = 0; // 0 to 63 LEDs in the matrix
int columnLevel = 0; // pixel value converted into LED column
int rowLevel    = 0; // pixel value converted into LED row

void setup() 
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(columnPins[i], OUTPUT);  // make all the LED pins outputs
    pinMode(rowPins[i], OUTPUT);
  }
}

void loop() 
{
  int sensorValue = analogRead(0);             // read the analog in value
  pixel = map(sensorValue, 0, 1023, 0, 63);    // map sensor value to pixel (LED)


  columnLevel = pixel / 8;  // map to the number of columns
  rowLevel = pixel % 8;     // get the fractional value

  for (int column = 0; column < 8; column++)
  {
    digitalWrite(columnPins[column], LOW);     // connect this column to GND
    for(int row = 0; row < 8; row++)
    {
      if (columnLevel > column)
      {
        digitalWrite(rowPins[row], HIGH);  // connect all LEDs in row to + voltage
      }
      else if (columnLevel == column && rowLevel >= row)
      {
          digitalWrite(rowPins[row], HIGH);
      }
      else
      {
        digitalWrite(columnPins[column], LOW); // turn off all LEDs in this row
      }
      delayMicroseconds(300);    // delay gives frame time of 20ms for 64 LEDs
      digitalWrite(rowPins[row], LOW);  // turn off LED
    }

    // disconnect this column from Ground
    digitalWrite(columnPins[column], HIGH);   
  }
}
