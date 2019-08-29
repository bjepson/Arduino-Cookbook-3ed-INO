// BinaryDataFromProcessing for Serial1
// These defines must mirror the sending program:
const char HEADER       = 'H';
const char MOUSE_TAG    = 'M';
const int  TOTAL_BYTES  = 6  ; // the total bytes in a message

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {
  if ( Serial.available() >= TOTAL_BYTES)
  {
    if ( Serial.read() == HEADER)
    {
      char tag = Serial.read();
      if (tag == MOUSE_TAG)
      {
        int x = Serial.read() * 256;
        x = x + Serial.read();
        int y = Serial.read() * 256;
        y = y + Serial.read();
        Serial1.println();
        Serial1.println("Got mouse msg:");
        Serial1.print("x=");   Serial1.print(x);
        Serial1.print(", y="); Serial1.print(y);
      }
      else
      {
        Serial1.println();
        Serial1.print("Unknown tag: ");
        Serial1.write(tag); Serial1.println();
      }
    }
  }
}
