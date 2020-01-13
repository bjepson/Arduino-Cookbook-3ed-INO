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
  int sleepTimeMillis1 = Watchdog.sleep(500);

  digitalWrite(LED_BUILTIN, LOW);
  int sleepTimeMillis2 = Watchdog.sleep(500);

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
