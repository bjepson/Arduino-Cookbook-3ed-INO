/*
 * Free memory sketch for AVR
 */

String s = "\n";

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(memoryFree());  // print the free memory
  //s = s + "Hello I am Arduino\n";
  Serial.println(s);           // print the string value
  delay(3000);
}

// Variable created by the build process when compiling the sketch
extern int *__brkval; // Pointer to last address allocated on the heap (or 0)

// function to return the amount of free RAM
int memoryFree()
{
  int freeValue; // This will be the most recent object allocated on the stack
  if((int)__brkval == 0) // Heap is empty; use start of heap
  {
    freeValue = ((int)&freeValue) - ((int)__malloc_heap_start);
  }
  else // Heap is not empty; use last heap address
  {
    freeValue = ((int)&freeValue) - ((int)__brkval);
  }
  return freeValue;
}
