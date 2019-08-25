/*
   ForLoop sketch
   demonstrates for loop
*/

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // this goes in setup()
}

void loop() {
  Serial.println("for(int i=0; i < 4; )");
  for(int i=0; i < 4; )
  {
    Serial.println(i);
    if(digitalRead(2) == LOW) {
      i++;  // only increment the value if the button is pressed
    }
  }

  int j;

  Serial.println("for(j=0; j < 4; j++ )");
  for (j = 0; j < 4; j++ )
  {
    Serial.println(j);
  }

  int k = 1;

  Serial.println("for(   ; k < 4; k++ )");
  for (  ; k < 4; k++ )
  {
    Serial.println(k);
  }
  delay(1000);
}
