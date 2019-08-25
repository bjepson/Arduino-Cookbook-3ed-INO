// bitFunctions
// demonstrates using the bit functions

byte flags = 0; // these examples set, clear or read bits in a variable called flags.

// bitSet example
void setFlag(int flagNumber)
{
   bitSet(flags, flagNumber);
}

// bitClear example
void clearFlag(int flagNumber)
{
   bitClear(flags, flagNumber);
}

// bitPosition example

int getFlag(int flagNumber)
{
   return bitRead(flags, flagNumber);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    flags = 0;   // clear all flags
    showFlags();
    setFlag(2);  // set some flags;
    setFlag(5);
    showFlags();
    clearFlag(2);
    showFlags();

    delay(10000); // wait a very long time
}

// reports flags that are set
void showFlags()
{
    for(int flag=0; flag < 8; flag++)
    {
      if (getFlag(flag) == true)
         Serial.print("* bit set for flag ");      else
         Serial.print("bit clear for flag ");

      Serial.println(flag);
    }
    Serial.println();
}
