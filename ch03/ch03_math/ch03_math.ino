void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  int myValue;
  myValue = 1 + 2;  // addition
  myValue = 3 - 2;  // subtraction
  myValue = 3 * 2;  // multiplication
  myValue = 3 / 2;  // division (the result is 1)
  myValue * 2;
  {
    int value =   1 + 2 * 3 + 4;
    value * 2;
  }
  {
    int value =   ((1 + 2) * 3) + 4;
    value * 2;
  }

  {
    // 60 seconds in a minute, 60 minutes in an hour, 24 hours in a day
    long seconds_per_day = 60 * 60 * 24;
    Serial.println(seconds_per_day);
  }
  {
    long seconds_per_day = 60L * 60 * 24;
    Serial.println(seconds_per_day);
  }
  {
    long seconds_per_day_plus_one = 1L + 60 * (60 * 24);
    Serial.println(seconds_per_day_plus_one);
  }
  {
    long seconds_per_day_plus_one = 1 + 60 * (60L * 24);
    Serial.println(seconds_per_day_plus_one);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
