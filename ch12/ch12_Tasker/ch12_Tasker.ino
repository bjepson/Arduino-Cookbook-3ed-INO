#define TASKER_MAX_TASKS 2 // Set this to the number of tasks you need
#include <Tasker.h>

// Declare the Tasker object
Tasker tasker;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, OUTPUT);

  // Blink the built-in LED every second
  tasker.setInterval(blink, 1000, LED_BUILTIN);

  // Blink the LED on pin 10 twice per second
  tasker.setInterval(blink, 500, 10);
}

void loop()
{
  tasker.loop(); // Run any pending tasks
}

void blink(int pinNumber)
{
  bool ledState = !digitalRead(pinNumber); // Toggle the current pin state
  if (ledState)
  {
    digitalWrite(pinNumber, HIGH);
  }
  else
  {
    digitalWrite(pinNumber, LOW);
  }
}
