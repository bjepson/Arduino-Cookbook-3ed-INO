/*
   Mouse
   an arduino sketch using ps2 mouse library
   from http://www.arduino.cc/playground/ComponentLib/Ps2mouse
 */

#include <ps2.h>

const int dataPin =  5;
const int clockPin = 6;

const int xLedPin  = 9; // Use pin 8 on the MKR boards
const int yLedPin  = 10;

const int mouseRange = 255;  // the maximum range of x/y values

char x;                 // values read from the mouse
char y;
byte status;
  
int xPosition = 0;      // values incremented and decremented when mouse moves
int yPosition = 0;
int xBrightness = 128;  // values increased and decreased based on mouse position
int yBrightness = 128;

const byte REQUEST_DATA = 0xeb; // command to get data from the mouse

PS2 mouse(clockPin, dataPin); // Declare the mouse object

void setup()
{
  Serial.begin(9600);
  mouseBegin(); // Initialize the mouse
}

void loop()
{
  // get a reading from the mouse
  mouse.write(REQUEST_DATA); // ask the mouse for data
  mouse.read();      // ignore ack

  status = mouse.read(); // read the mouse buttons
  if(status & 1) // this bit is set if the left mouse btn pressed
    xPosition = 0; // center the mouse x position
  if(status & 2) // this bit is set if the right mouse btn pressed
    yPosition = 0; // center the mouse y position

  x = mouse.read();
  y = mouse.read();
  if( x != 0 || y != 0)
  {
    // here if there is mouse movement

    xPosition = xPosition + x; // accumulate the position
    xPosition = constrain(xPosition,-mouseRange,mouseRange);

    xBrightness = map(xPosition, -mouseRange, mouseRange, 0,255);
    analogWrite(xLedPin, xBrightness);

    yPosition = constrain(yPosition + y, -mouseRange,mouseRange);
    yBrightness = map(yPosition, -mouseRange, mouseRange, 0,255);
    analogWrite(yLedPin, yBrightness);
    printValues(); // show button and x and y values on Serial Monitor/Plotter
  }
}

void mouseBegin()
{
  // reset and initialize the mouse
  mouse.write(0xff);         // reset
  delayMicroseconds(100);
  mouse.read();              // ack byte
  mouse.read();              // blank
  mouse.read();              // blank
  mouse.write(0xf0);         // remote mode
  mouse.read();              // ack
  delayMicroseconds(100);
}

void printValues()
{
  Serial.print("X:");
  Serial.print(xPosition);
  Serial.print(",Y:");
  Serial.print(yPosition);
  Serial.println();
}
