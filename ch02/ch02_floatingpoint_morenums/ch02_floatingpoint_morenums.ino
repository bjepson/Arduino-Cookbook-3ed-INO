/*
   Floating-point example
   This sketch initialized a float value to 1.1
   It repeatedly reduces the value by 0.1 until the value is 0
*/

float value = 1.1;


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  testPrecision(1.1, 0);
  testPrecision(11.1, 10);
  testPrecision(101.1, 100);
  testPrecision(1001.1, 1000);
  delay(2500);
}

void testPrecision(float a, float b)
{
  float decrement = 0.1;
  while (a >= b - decrement) {
    if (almostEqual(a, b)) {
      Serial.print("The value ");
      Serial.print(a, 7); // print to 7 decimal places
      Serial.print(" is almost equal to ");
      Serial.println(b, 7); // print to 7 decimal places
    }
    a = a - decrement;
  }
}

// returns true if the difference between a and b is small
int almostEqual(float a, float b)
{
  const float DELTA = .00001; // max difference to be almost equal

  if (a == 0) return fabs(b) <= DELTA;
  if (b == 0) return fabs(a) <= DELTA;

  float diff_unscaled = fabs(a - b);
  float diff_scaled   = fabs((a - b) / max(fabs(a), fabs(b)));
  if (diff_scaled <= DELTA)
  {
    Serial.print("Unscaled: ");
    Serial.print(diff_unscaled, 7);
    Serial.print(" Scaled: ");
    Serial.println(diff_scaled, 7);
    return 1;
  }
  return 0;
}
