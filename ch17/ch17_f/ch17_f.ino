/*
 * Write strings using Program memory (Flash)
 */
 
void setup()
{
  Serial.begin(9600); 
}

void loop()
{
  Serial.println(memoryFree());  // print the free memory

  Serial.println(F("Arduino"));  // print the string
  delay(1000);
}

#ifdef __arm__
// Variable created by the build process when compiling the sketch
extern "C" char *sbrk(int incr); // Call with 0 to get start address of free ram
#else
extern int *__brkval; // Pointer to last address allocated on the heap (or 0)
#endif

// function to return the amount of free RAM
int memoryFree()
{
  int freeValue; // This will be the most recent object allocated on the stack
#ifdef __arm__
  freeValue = &freeValue - reinterpret_cast<int*>(sbrk(0));
#else
  if((int)__brkval == 0) // Heap is empty; use start of heap
  {
    freeValue = ((int)&freeValue) - ((int)__malloc_heap_start);
  }
  else // Heap is not empty; use last heap address
  {
    freeValue = ((int)&freeValue) - ((int)__brkval);
  }
#endif
  return freeValue;
}
