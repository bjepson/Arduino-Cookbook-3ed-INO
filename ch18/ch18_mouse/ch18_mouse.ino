/*
 * Mouse Emulation sketch
 * Use the Mouse library to emulate a USB mouse device
 */

#include "Mouse.h"

const int buttonPin = 2; // left click
const int potXPin = A4;   // analog pins for pots
const int potYPin = A5;

int last_x = 0;
int last_y = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  // Get initial potentiometer positions. Range is -127 to 127
  last_x = (512 - (int) analogRead(potXPin)) / 4;
  last_y = (512 - (int) analogRead(potYPin)) / 4;
  
  Mouse.begin();
}

void loop()
{
  // Get current positions.
  int x = (512 - (int) analogRead(potXPin)) / 4;
  int y = (512 - (int) analogRead(potYPin)) / 4;

  Serial.print("last_x: "); Serial.println(last_x);
  Serial.print("last_y: "); Serial.println(last_y);
  Serial.print("x: "); Serial.println(x);
  Serial.print("y: "); Serial.println(y);
  
  // calculate the movement distance based on the potentiometer state
  int xDistance = last_x - x;
  int yDistance = last_y - y;

  // Update last known positions of the potentiometer
  last_x = x;
  last_y = y;

  // if X or Y movement is greater than 3, move:
  if (abs(xDistance) > 3 || abs(yDistance) > 3) 
  {
    Serial.print("x move: "); Serial.println(xDistance);
    Serial.print("y move: "); Serial.println(yDistance);
    Mouse.move(xDistance, yDistance, 0);
  }

  // if the mouse button is pressed:
  if (digitalRead(buttonPin) == LOW) 
  {
    if (!Mouse.isPressed(MOUSE_LEFT)) 
    {
      Mouse.press(MOUSE_LEFT); // Click
    }
  }
  else 
  {
    if (Mouse.isPressed(MOUSE_LEFT)) 
    {
      Mouse.release(MOUSE_LEFT); // Release
    }
  }
  Serial.println();
  delay(10);
}
