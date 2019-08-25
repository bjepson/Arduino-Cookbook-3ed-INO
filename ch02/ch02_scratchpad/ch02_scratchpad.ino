#include <SdFat.h>
#include <float.h>

ArduinoOutStream cout(Serial);
char str[] = "Arduino";
// The setup() method runs once, when the sketch starts
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // initialize the onboard LED as an output
  Serial.begin(9600);

}

// the loop() method runs over and over again,
void loop()
{

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
  delay(1000);                       // wait a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
  delay(1000);                       // wait a second
  if (Serial.available()) {

    cout << "sizeof char: "          << sizeof(char)          << " (bits: " << CHAR_BIT << ", range " << CHAR_MIN << " to " << CHAR_MAX << ")\n";
    cout << "sizeof signed char: "   << sizeof(signed char)   << " (range " << SCHAR_MIN << " to " << SCHAR_MAX << ")\n";
    cout << "sizeof unsigned char: " << sizeof(unsigned char) << " (range 0 to " << UCHAR_MAX << ")\n";
    cout << "sizeof int: "           << sizeof(int)           << " (range " << INT_MIN << " to " << INT_MAX << ")\n";
    cout << "sizeof short int: "     << sizeof(short int)     << " (range " << SHRT_MIN << " to " << SHRT_MAX << ")\n";
    cout << "sizeof unsigned short int: " << sizeof(unsigned short int) << " (range 0 to " << USHRT_MAX << ")\n";
    cout << "sizeof long int: " << sizeof(long int) << " (range " << LONG_MIN << " to " << LONG_MAX << ")\n";
    cout << "sizeof unsigned long int: " << sizeof(unsigned long int) << " (range 0 to " << ULONG_MAX << ")\n";
    cout << "sizeof float: " << sizeof(float) << " (range " << FLT_MIN << " to " << FLT_MAX - 1 << ")\n";
    while (Serial.read());
  }
  if (strcmp(str, "Arduino!") == 0)
  {
    cout << "hey dude\n";
    // do something if the variable str is equal to "Arduino"
  }
}
