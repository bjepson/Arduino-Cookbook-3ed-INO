/*
   SoftwareSerialOutput sketch
   Output data to a software serial port
*/

#define serial_lcd Serial1

void setup()
{
  Serial.begin(9600); // 9600 baud for the built-in serial port
  serial_lcd.begin(9600); //initialize the software serial port also for 9600
}

int number = 0;

void loop()
{
  serial_lcd.print("Number: ");  // send text to the LCD
  serial_lcd.println(number);    // print the number on the LCD
  Serial.print("Number: ");
  Serial.println(number);        // print the number on the PC console

  delay(500); // delay half second between numbers
  number++;   // to the next number
}
