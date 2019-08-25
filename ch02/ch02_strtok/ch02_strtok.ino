/*
 * SplitSplit sketch
 * split a comma-separated string
 */

const int  MAX_STRING_LEN = 20; // set this to the largest string
                                // you will process
                                
char stringList[] = "Peter,Paul,Mary"; // an example string

char stringBuffer[MAX_STRING_LEN+1]; // a static buffer for computation and output

void setup()
{
  Serial.begin(9600);
  while(!Serial); // See #serial_output_begin_wait

  char *str;
  char *p;
  strncpy(stringBuffer, stringList, MAX_STRING_LEN); // copy source string
  Serial.println(stringBuffer);                      // show the source string
  
  for( str = strtok_r(stringBuffer, ",", &p);        // split using comma
       str;                                          // loop while str is not null
       str = strtok_r(NULL, ",", &p)                 // get subsequent tokens
     )
  {
    Serial.println(str);
  }
}

void loop()
{
}
