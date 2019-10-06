/*
 * PixelBarGraph.ino
 * Sensor value determines how many LEDs to light
 */

#include <Adafruit_NeoPixel.h>

const int sensorPin = A0; // analog pin for sensor

const int ledsPin = 2;   // the pin the LED strip is connected to
const int numOfLeds = 16; // how many LEDs in the strip

//used to automatically map sensor values
const int minReading = 0;
const int maxReading = 1023;

//declare led strip
Adafruit_NeoPixel leds = Adafruit_NeoPixel(numOfLeds, ledsPin, NEO_GRB + NEO_KHZ800);

void setup() {
  leds.begin();   //initialise led strip
  leds.setBrightness(25);
}

void loop() {
  int sensorReading =  analogRead(A0);
  int nbrLedsToLight = map(sensorReading, minReading, maxReading, 0, numOfLeds);

  for (int i = 0; i < numOfLeds; i++)
  {
    if ( i < nbrLedsToLight)
      leds.setPixelColor(i, leds.Color(0, 0, 255)); // blue
    else
      leds.setPixelColor(i, leds.Color(0, 255, 0)); // green
  }
  leds.show();
}
