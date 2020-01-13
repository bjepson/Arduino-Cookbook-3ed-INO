/*
   glcd
 */

#include <glcd.h>

#include "fonts/SystemFont5x7.h"   // system font
int count = 0;

void setup()
{
  GLCD.Init(NON_INVERTED);          // initialize the library
  GLCD.ClearScreen();
  GLCD.SelectFont(System5x7);       // select fixed width system font
  GLCD.print("hello world");        // print a message
  delay(3000);
}


void loop()
{

    GLCD.ClearScreen();
    GLCD.DrawRect(0, 0, 64, 61, BLACK); // rectangle in left side of screen
    // rounded rectangle around text area
    GLCD.DrawRoundRect(68, 0, 58, 61, 5, BLACK);
    for(int i=0; i < 62; i += 4)
    {
      // draw lines from upper left down right side of rectangle
      GLCD.DrawLine(1,1,63,i, BLACK);
    }
    GLCD.DrawCircle(32,31,30,BLACK);   // circle centered on left side of screen
    GLCD.FillRect(92,40,16,16, WHITE); // clear previous spinner position
    GLCD.CursorTo(5,5);                // locate cursor for printing text
    GLCD.PrintNumber(count);           // print a number at current cursor position
    count = count + 1;
    delay(1000);
}
