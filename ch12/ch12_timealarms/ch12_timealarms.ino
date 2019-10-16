/*
 * TimeAlarmsExample sketch
 *
 * This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
 * and simulates turning lights on at night and off in the morning
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 *
 * At startup the time is set to Jan 1 2020  8:29 am
 */

#include <TimeLib.h>
#include <TimeAlarms.h>

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("TimeAlarms Example");
  Serial.println("Alarms are triggered daily at 8:30 am and 17:45 pm");
  Serial.println("One timer is triggered every 15 seconds");
  Serial.println("Another timer is set to trigger only once after 10 seconds");
  Serial.println();

  setTime(8,29,40,1,1,2020); // set time to 8:29:40am Jan 1 2020

  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day

  Alarm.timerRepeat(15, RepeatTask);            // timer for every 15 seconds
  Alarm.timerOnce(10, OnceOnlyTask);            // called once after 10 seconds
}

void MorningAlarm()
{
  Serial.println("Alarm: - turn lights off");
}

void EveningAlarm()
{
  Serial.println("Alarm: - turn lights on");
}

void RepeatTask()
{
  Serial.println("15 second timer");
}

void OnceOnlyTask()
{
  Serial.println("This timer only triggers once");
}

void loop()
{
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

// Pad digits with a leading 0
String padDigits(int digit)
{
  String str = String("0") + digit; // Put a zero in front of the digit
  return str.substring(str.length() - 2); // Remove all but the last two characters
}

void digitalClockDisplay(){
  String timestr = String(hour()) + ":" + padDigits(minute()) +
                   ":" + padDigits(second());
  Serial.println(timestr);
  
  String datestr = String(year()) + "-" + padDigits(month()) + 
                   "-" + padDigits(day()); 
  Serial.println(datestr);
}
