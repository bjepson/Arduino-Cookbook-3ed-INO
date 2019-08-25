void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  char string1[ ] = "left";
  char string2[ ] = "right";

  if (strcmp(string1, string2) == 0)
  {
    Serial.println("strings are equal");
  }

  if (strcmp("left", "leftcenter") == 0)  // this will evaluate to false
  {
    Serial.println("True");
  }
  else
  {
    Serial.println("False");
  }

  if (strncmp("left", "leftcenter", 4) == 0)  // this will evaluate to true
  {
    Serial.println("True");
  }
  else
  {
    Serial.println("False");
  }

  String stringOne = String("this");
  if (stringOne == "this")
  {
    Serial.println("this will be true");
  }
  if (stringOne == "that")
  {
    Serial.println("this will be false");
  }


}
