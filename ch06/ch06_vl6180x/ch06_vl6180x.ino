/* tof-distance sketch
 * prints distance and changes LED flash rate based on distance from sensor
 */
 
#include <Wire.h>
#include "Adafruit_VL6180X.h"

Adafruit_VL6180X sensor = Adafruit_VL6180X();

const int ledPin  = LED_BUILTIN; // LED pin

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (! sensor.begin()) {
    Serial.println("Could not initialize VL6180X");
    while (1);
  }
}

void loop() {

  // Read the range and check the status for any errors
  byte cm     = sensor.readRange();
  byte status = sensor.readRangeStatus();

  if (status == VL6180X_ERROR_NONE)
  {
    Serial.println(cm);

    digitalWrite(ledPin, HIGH);
    delay(cm * 10); // each centimeter adds 10 milliseconds delay
    digitalWrite(ledPin, LOW);
    delay(cm * 10);

  }
  else
  {
    // Major errors are worth mentioning
    if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
      Serial.println("System error");
    }
  }
  delay(50);
}
