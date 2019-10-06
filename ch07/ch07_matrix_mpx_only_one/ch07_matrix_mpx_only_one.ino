/*
 * matrixMpx sketch, one at a time
 *
 * Sequence LEDs starting from first column and row, one at a time
 * Multiplexing is used to control 64 LEDs with 16 pins
 */

const int columnPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int rowPins[]    = {10,11,12,A1,A2,A3,A4,A5};

int pixel = 0; // 0 to 63 LEDs in the matrix

void setup() 
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(columnPins[i], OUTPUT);  // make all the LED pins outputs
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(columnPins[i], HIGH);   
  }
}

void loop() 
{
  pixel = pixel + 1;
  if(pixel > 63)
     pixel = 0;

  int column = pixel / 8;  // map to the number of columns
  int row = pixel % 8;     // get the fractional value

  digitalWrite(columnPins[column], LOW);  // Connect this column to GND
  digitalWrite(rowPins[row], HIGH);       // Take this row HIGH
  
  delay(125);  // pause briefly

  digitalWrite(rowPins[row], LOW);        // Take the row low  
  digitalWrite(columnPins[column], HIGH); // Disconnect the column from GND
 
}
