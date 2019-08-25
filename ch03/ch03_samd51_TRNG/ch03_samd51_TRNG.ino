/* Copyright 2019 Ron Sutton

https://github.com/SapientHetero/TRNG-for-ATSAMD51J19A-Adafruit-Metro-M4-

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

extern "C" {
  #include "trngFunctions.h"
}

#define highWord(w) ((w) >> 16)
#define lowWord(w) ((w) & 0xffff)

// M4 True Random Number Generator (TRNG) Example Code 
void setup() 
{
  Serial.begin(500000);                        // Initialise the Serial port
  while(!Serial);                              // Wait for the console to be started

  trngInit();                                  // Initialize the TRNG
}

void loop() {
  
  uint32_t r = trngGetRandomNumber();

  int loWord = lowWord(r);
  int hiWord = highWord(r);
  Serial.print((char) highByte(hiWord));
  Serial.print((char) lowByte(hiWord));
  Serial.print((char) highByte(loWord));
  Serial.print((char) lowByte(loWord));
  delay(1);
  
}
