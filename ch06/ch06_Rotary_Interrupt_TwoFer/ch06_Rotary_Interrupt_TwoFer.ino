/* Two Rotary Encoder Library example
 * Read the rotary encoder with a library that uses interrrupts 
 * to process the encoder's activity
 */

#include <Encoder.h>

Encoder myEncA(2, 3); // MKR boards use pins 4, 5
Encoder myEncB(6, 7); // Mega boards use pins 18, 19

void setup()
{
  Serial.begin(9600);
  while(!Serial);
}

long lastA  = -999;
long lastB  = -999;

void loop()
{
  long currentA = myEncA.read();
  long currentB = myEncB.read();
  if (currentA != lastA || currentB != lastB) { // If either position changed
    lastA = currentA; // Save both positions
    lastB = currentB;

    // Print the positions to the Serial Monitor (or Serial Plotter)
    Serial.print("A:"); Serial.print(currentA);
    Serial.print(" ");
    Serial.print("B:"); Serial.println(currentB);
  }
}
