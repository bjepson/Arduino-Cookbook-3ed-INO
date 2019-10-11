/*
   7219 Matrix demo
*/

#include <MD_MAX72xx.h>

// Pins to control 7219
#define LOAD_PIN 2
#define CLK_PIN  3
#define DATA_PIN 4

// Configure the hardware
#define MAX_DEVICES  1
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, LOAD_PIN, MAX_DEVICES);

void setup()
{
  mx.begin();
}

void loop()
{
  mx.clear(); // Clear the display

  // Draw rows and columns
  for (int r = 0; r < 8; r++)
  {
    for (int c = 0; c < 8; c++) {
      mx.setPoint(r, c, true); // Light each LED
      delay(50);
    }

    // Cycle through available brightness levels
    for (int k = 0; k <= MAX_INTENSITY; k++) {
      mx.control(MD_MAX72XX::INTENSITY, k);
      delay(100);
    }
  }
}
