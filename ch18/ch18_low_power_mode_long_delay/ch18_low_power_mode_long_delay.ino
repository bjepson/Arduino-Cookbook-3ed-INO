/*
 * Low power sketch
 * Reduce power usage with the Adafruit SleepyDog library
 */
#include <Adafruit_SleepyDog.h>

void setup() 
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);
  unsigned long sleepTimeMillis1 = longDelay(8600);

  digitalWrite(LED_BUILTIN, LOW);
  unsigned long sleepTimeMillis2 = longDelay(8600);

// Try to restore USB connection on Leonardo and other boards
// with Native USB.
#if defined(USBCON) && !defined(USE_TINYUSB)
  USBDevice.attach();
#endif

  Serial.print("Slept for "); Serial.print(sleepTimeMillis1);
  Serial.print("ms and "); Serial.print(sleepTimeMillis2);
  Serial.println("ms");
  delay(100); // Give the serial buffer time to transmit
}

unsigned long longDelay(long milliseconds)
{
  unsigned long sleptFor = 0;
  while(milliseconds > 0)
  {
    if(milliseconds > 8000)
    {
      milliseconds -= 8000;
      sleptFor += Watchdog.sleep(8000);
    }
    else
    {
      sleptFor += Watchdog.sleep(milliseconds);
      break;
    }
  }
  return sleptFor;
}
