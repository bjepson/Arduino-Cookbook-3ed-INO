/*
 * EEPROM sketch based on Blink without Delay
 * uses EEPROM to store blink values
 */

#include <EEPROM.h>

// these values are saved in EEPROM
const byte EEPROM_ID = 0x99;   // used to identify if valid data in EEPROM
byte ledPin =  LED_BUILTIN;    // the LED pin
int interval = 1000;           // interval at which to blink (milliseconds)

// variables that do not need to be saved
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

//constants used to identify EEPROM addresses
const int ID_ADDR = 0;       // the EEPROM address used to store the ID
const int PIN_ADDR = 1;      // the EEPROM address used to store the pin
const int INTERVAL_ADDR = 2; // the EEPROM address used to store the interval

void setup()
{
  Serial.begin(9600);
  byte id = EEPROM.read(ID_ADDR); // read the first byte from the EEPROM
  if( id == EEPROM_ID)
  {
    // here if the id value read matches the value saved when writing eeprom
    Serial.println("Using data from EEPROM");
    ledPin = EEPROM.read(PIN_ADDR);
    byte hiByte  = EEPROM.read(INTERVAL_ADDR);
    byte lowByte = EEPROM.read(INTERVAL_ADDR+1);
    interval =  word(hiByte, lowByte); // see word function in Recipe 3.15
  }
  else
  {
    // here if the ID is not found, so write the default data
    Serial.println("Writing default data to EEPROM");
    EEPROM.write(ID_ADDR,EEPROM_ID); // write the ID to indicate valid data
    EEPROM.write(PIN_ADDR, ledPin); // save the pin in eeprom
    byte hiByte = highByte(interval);
    byte loByte = lowByte(interval);
    EEPROM.write(INTERVAL_ADDR, hiByte);
    EEPROM.write(INTERVAL_ADDR+1, loByte);
  }
  Serial.print("Setting pin to ");
  Serial.println(ledPin,DEC);
  Serial.print("Setting interval to ");
  Serial.println(interval);

  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // this is the same code as the BlinkWithoutDelay example sketch
  if (millis() - previousMillis > interval)
  {
    previousMillis = millis();     // save the last time you blinked the LED
    // if the LED is off turn it on and vice versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(ledPin, ledState);  // set LED using value of ledState
  }
  processSerial();
}

// function to get duration or pin values from Serial Monitor
// value followed by  i is interval, p is pin number
int value = 0;
void processSerial()
{
   if( Serial.available())
  {
    char ch = Serial.read();
    if(ch >= '0' && ch <= '9') // is this an ascii digit between 0 and 9?
    {
       value = (value * 10) + (ch - '0'); // yes, accumulate the value
    }
    else if (ch == 'i')  // is this the interval
    {
       interval = value;
       Serial.print("Setting interval to ");
       Serial.println(interval);
       byte hiByte = highByte(interval);
       byte loByte = lowByte(interval);
       EEPROM.write(INTERVAL_ADDR, hiByte);
       EEPROM.write(INTERVAL_ADDR+1, loByte);
       value = 0; // reset to 0 ready for the next sequence of digits
    }
    else if (ch == 'p')  // is this the pin number
    {
       ledPin = value;
       Serial.print("Setting pin to ");
       Serial.println(ledPin,DEC);
       pinMode(ledPin, OUTPUT);
       EEPROM.write(PIN_ADDR, ledPin); // save the pin in eeprom
       value = 0; // reset to 0 ready for the next sequence of digits
    }
  }
}
