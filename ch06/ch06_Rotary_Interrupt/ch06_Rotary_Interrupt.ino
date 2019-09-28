/* Rotary Encoder library sketch
 * Read the rotary encoder with a library that uses interrrupts 
 * to process the encoder's activity
 */

#include <Encoder.h>

Encoder myEnc(2, 3); // On MKR boards, use pins 6, 7

void setup()
{
  Serial.begin(9600);
}

long lastPosition = -999;

void loop()
{
  long currentPosition = myEnc.read();
  if (currentPosition != lastPosition) { // If the position changed
    lastPosition = currentPosition;  // Save the last position
    Serial.println(currentPosition); // print it to the Serial monitor
  }
}
