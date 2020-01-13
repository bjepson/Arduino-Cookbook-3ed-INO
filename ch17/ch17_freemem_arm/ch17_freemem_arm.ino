/*
 * Free memory sketch for ARM
 */

String s = "\n";

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(memoryFree());  // print the free memory
  s = s + "Hello I am Arduino\n";
  Serial.println(s);           // print the string value
  delay(3000);
}

// Variable created by the build process when compiling the sketch
extern "C" char *sbrk(int incr); // Call with 0 to get start address of free ram

// function to return the amount of free RAM
int memoryFree()
{
  int freeValue; // This will be the most recent object allocated on the stack
  freeValue = &freeValue - reinterpret_cast<int*>(sbrk(0));

  return freeValue;
}
