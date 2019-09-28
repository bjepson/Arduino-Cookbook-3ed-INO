/* Rotary Encoder library sketch
   Read the rotary encoder with a library that uses interrrupts
   to process the encoder's activity
*/

#include <Encoder.h>

Encoder myEnc(2, 3); // On MKR boards, use pins 6, 7

long runningAverage = 0;      // the running average of calculated values
const int averagedOver = 4;   // how quickly new values affect running average
                              // bigger numbers mean slower
void setup()
{
  Serial.begin(9600);
}

long lastPosition = -999;

void loop()
{
  long currentPosition = myEnc.read();
  // calculate running average
  runningAverage=(((averagedOver-1)*runningAverage)+currentPosition)/averagedOver;
  
  if (runningAverage != lastPosition) { // If the position changed
    lastPosition = runningAverage;  // Save the last position
    Serial.println(runningAverage); // print it to the Serial monitor
  }
}
