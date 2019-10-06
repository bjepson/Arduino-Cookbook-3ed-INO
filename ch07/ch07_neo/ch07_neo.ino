/*
 * SimplePixel sketch
 * LED color changes with sensor value
 */

#include <Adafruit_NeoPixel.h>

const int sensorPin = A0; // analog pin for sensor
const int ledPin = 6;     // the pin the LED strip is connected to
const int count  = 16;     // how many LEDs in the strip

// declare led strip
Adafruit_NeoPixel leds = Adafruit_NeoPixel(count, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  leds.begin(); // initialise led strip
  for (int i = 0; i < count; i++) {
    leds.setPixelColor(i, leds.Color(0,0,0)); // turn each LEDs off
  }
  leds.show();  // refresh the strip with the new pixel values (all off)
}

void loop() {
  static unsigned int last_reading = -1;

  int reading =  analogRead(sensorPin);
  if (reading != last_reading) { // If the value has changed

    // Map the analog reading to the color range of the NeoPixel
    unsigned int mappedSensorReading = map(reading, 0, 1023, 0, 65535);

    // Update the pixels with a slight delay to create a sweeping effect
    for (int i = 0; i < count; i++) {
      leds.setPixelColor(i, leds.gamma32(leds.ColorHSV(mappedSensorReading, 255, 128)));
      leds.show();
      delay(25);
    }
    last_reading = reading;
  }
}
