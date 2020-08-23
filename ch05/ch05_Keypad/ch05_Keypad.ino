/*
  Keypad sketch
  prints the key pressed on a keypad to the serial port
*/

const int numRows = 4;       // number of rows in the keypad
const int numCols = 3;       // number of columns
const int debounceTime = 20; // number of milliseconds for switch to be stable

// keymap defines the character returned when the corresponding key is pressed
const char keymap[numRows][numCols] = {
  { '1', '2', '3'  } ,
  { '4', '5', '6'  } ,
  { '7', '8', '9'  } ,
  { '*', '0', '#'  }
};

// this array determines the pins used for rows and columns
const int rowPins[numRows] = {8, 7, 6, 5}; // Rows 0 through 3
const int colPins[numCols] = {4, 3, 2};    // Columns 0 through 2

void setup()
{
  Serial.begin(9600);
  for (int row = 0; row < numRows; row++)
  {
    pinMode(rowPins[row],INPUT_PULLUP); // Set row pins as input with pullups
  }
  for (int column = 0; column < numCols; column++)
  {
    pinMode(colPins[column],OUTPUT);     // Set column pins as outputs 
    digitalWrite(colPins[column],HIGH);  // Make all columns inactive
  }
}

void loop()
{
  char key = getKey();
  if( key != 0) { // if the character is not 0 then it's a valid key press
    Serial.print("Got key ");
    Serial.println(key);
  }
}

// returns with the key pressed, or 0 if no key is pressed
char getKey()
{
  char key = 0;                                  // 0 indicates no key pressed

  for(int column = 0; column < numCols; column++)
  {
    digitalWrite(colPins[column],LOW);         // Activate the current column.
    for(int row = 0; row < numRows; row++)     // Scan all rows for 
                                               // a key press.
    {
      if(digitalRead(rowPins[row]) == LOW)     // Is a key pressed?
      {
        delay(debounceTime);                   // debounce
        while(digitalRead(rowPins[row]) == LOW)
            ;                                  // wait for key to be released
        key = keymap[row][column];             // Remember which key 
                                               // was pressed.
        Serial.print("rowpin: "); Serial.print(rowPins[row]);
        Serial.print(" colpin: "); Serial.print(colPins[column]);
        Serial.print(" row: "); Serial.print(row);
        Serial.print(" col: "); Serial.println(column);
      }
    }
    digitalWrite(colPins[column],HIGH);     // De-activate the current column.
  }
  return key;  // returns the key pressed or 0 if none
}
