/*
   AnalogToJSON. Sends JSON-formatted representation of
   analog readings.
*/

void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  Serial.print("{");
  Serial.print("'A0': "); Serial.print(analogRead(A0)); Serial.print(", ");
  Serial.print("'A1': "); Serial.print(analogRead(A1)); Serial.print(", ");
  Serial.print("'A2': "); Serial.print(analogRead(A2)); Serial.print(", ");
  Serial.print("'A3': "); Serial.print(analogRead(A3)); Serial.print(", ");
  Serial.print("'A4': "); Serial.print(analogRead(A4)); Serial.print(", ");
  Serial.print("'A5': "); Serial.print(analogRead(A5)); Serial.print(", ");
  Serial.println("}");
}
