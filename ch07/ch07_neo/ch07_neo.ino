/*
 * SimplePixel.ino
 * LED color changes with sensor value
*/

#include <Adafruit_NeoPixel.h>

const int sensorPin = A0; // analog pin for sensor

const int ledPin = 6;   // the pin the LED strip is connected to
const int count  = 16;   // how many LEDs in the strip

//used to map sensor values
//you can alter these to suit the range of values from your sensor
const int minReading = 0;
const int maxReading = 1023;

//declare led strip
Adafruit_NeoPixel leds = Adafruit_NeoPixel(count, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  leds.begin();  //initialise led strip
}

void loop() {
  int value =  analogRead(sensorPin);
  int mappedSensorReading = map(value, minReading, maxReading, 0, 65535);

  for (int i = 0; i < count; i++) {
    leds.setPixelColor(i, leds.gamma32(leds.ColorHSV(mappedSensorReading, 255, 128)));
  }
  leds.show();
  delay(100);
}
