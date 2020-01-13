/*
 * multiple_alarms sketch
 * Has more timer repeats than the library supports out of the box -
 * you will need to edit the header file to enable more than 6 alarms
 */

#include <TimeLib.h>
#include <TimeAlarms.h>

int currentSeconds = 0;

void setup()
{
  Serial.begin(9600);

  // create 7 alarm tasks
  Alarm.timerRepeat(1, repeatTask1);
  Alarm.timerRepeat(2, repeatTask2);
  Alarm.timerRepeat(3, repeatTask3);
  Alarm.timerRepeat(4, repeatTask4);
  Alarm.timerRepeat(5, repeatTask5);
  Alarm.timerRepeat(6, repeatTask6);
  Alarm.timerRepeat(7, repeatTask7);  // 7th timer repeat
}

void repeatTask1()
{
  Serial.print("task 1  ");
}

void repeatTask2()
{
  Serial.print("task 2  ");
}
void repeatTask3()
{
  Serial.print("task 3  ");
}

void repeatTask4()
{
  Serial.print("task 4  ");
}

void repeatTask5()
{
  Serial.print("task 5  ");
}

void repeatTask6()
{
  Serial.print("task 6  ");
}

void repeatTask7()
{
  Serial.print("task 7  ");
}

void  loop()
{
  if(second() != currentSeconds)
  {
    // print the time for each new second
    // the task numbers will be printed when the alarm for that task is triggered
    Serial.println();
    Serial.print(second());
    Serial.print("->");
    currentSeconds = second();
    Alarm.delay(1); // Alarm.delay must be called to service the alarms
  }
}
