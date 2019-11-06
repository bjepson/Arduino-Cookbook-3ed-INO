/*
 * Two I2C Device sketch
 * Reads an air quality sensor and displays the VOC 
 * concentration on an LED display.
 */

#include <Adafruit_CCS811.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// Create objects for the sensor and display.
Adafruit_CCS811 ccs;
Adafruit_7segment matrix = Adafruit_7segment();

void setup() 
{
  Serial.begin(9600);
  if(!ccs.begin())
  {
    Serial.println("Could not start sensor.");
    while(1); // halt
  }
  while(!ccs.available()); // Wait until the sensor is ready

  matrix.begin(0x70); // Start the matrix

}

void loop() 
{
  if(ccs.available())
  {
    if(!ccs.readData())
    {
      int tvoc = ccs.getTVOC(); // Get the VOC concentration
      matrix.println(tvoc);     // Write the value
      matrix.writeDisplay();    // Update the display
    }
  }
  delay(500);
}
