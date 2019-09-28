/* Rotary Encoder Library example
 * Read the rotary encoder with a library that uses interrrupts 
 * to process the encoder's activity
 */

#include <Encoder.h>

Encoder myEnc(2, 3); // Use pins 4, 5 on the MKR family of boards

void setup() {
  Serial.begin(9600);
}

long lastPosition  = -999;

void loop() {
  
  long currentPosition = myEnc.read();
  if (currentPosition != lastPosition) {
    lastPosition = currentPosition;
    Serial.println(currentPosition);
  }
}
