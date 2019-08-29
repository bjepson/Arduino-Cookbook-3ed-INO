// BinaryDataFromProcessing
// These defines must mirror the sending program:
const char HEADER       = 'H';
const char MOUSE_TAG    = 'M';
const int  TOTAL_BYTES  = 6  ; // the total bytes in a message
                          
void setup()
{
  Serial.begin(9600);
}

void loop(){
  if ( Serial.available() >= TOTAL_BYTES)
  {
     if( Serial.read() == HEADER)
    {
      char tag = Serial.read();
      if(tag == MOUSE_TAG)
      {
        int x = Serial.read() * 256; 
        x = x + Serial.read();
        int y = Serial.read() * 256;
        y = y + Serial.read();
        Serial.println("Got mouse msg:");
        Serial.print("x=");    Serial.print(x);
        Serial.print(", y="); Serial.println(y);
      }
      else
      {
        Serial.print("Unknown tag: ");
        Serial.write(tag); Serial.println();
      }
    }
  }
}
