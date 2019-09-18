/*
 * Arduino Nano BLE Sense sensor demo
 */

#include <Arduino_APDS9960.h>
#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_LSM9DS1.h>

void setup() {
  
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) { // Initialize gesture/color/proximity sensor
    Serial.println("Could not initialize APDS9960.");
    while (1);
  }
  if (!HTS.begin()) {  // Initialize temperature/humidity sensor
    Serial.println("Could not initialize HTS221.");
    while (1);
  }
  if (!BARO.begin()) { // Initialize barometer
    Serial.println("Could not initialize LPS22HB.");
    while (1);
  }  
  if (!IMU.begin()) {  // Initialize inertial measurement unit
    Serial.println("Could not initialize LSM9DS1.");
    while (1);
  }

  prompt(); // Tell users what they can do.
}

void loop() {

  // If there's a gesture, run the appropriate function.
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
        readTemperature();
        break;

      case GESTURE_DOWN:
        readHumidity();
        break;

      case GESTURE_LEFT:
        readPressure();
        break;

      case GESTURE_RIGHT:
        Serial.println("Spin the gyro!\nx, y, z");
        for (int i = 0; i < 10; i++)
        {
          readGyro();
          delay(250);
        }
        break;

      default:
        break;
    }
    prompt(); // Show the prompt again
  }
}
void prompt() {
  Serial.println("\nSwipe!");
  Serial.println("Up for temperature, down for humidity");
  Serial.println("Left for pressure, right for gyro fun.\n");
}

void readTemperature()
{
  float temperature = HTS.readTemperature(FAHRENHEIT);
  Serial.print("Temperature: "); Serial.print(temperature);
  Serial.println(" °F");
}

void readHumidity() 
{
  float humidity = HTS.readHumidity();
  Serial.print("Humidity: "); Serial.print(humidity);
  Serial.println(" %");
}

void readPressure() 
{
  float pressure = BARO.readPressure(PSI);
  Serial.print("Pressure: "); Serial.print(pressure);
  Serial.println(" psi");
}

void readGyro() 
{
  float x, y, z;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    Serial.print(x); Serial.print(", ");
    Serial.print(y); Serial.print(", ");
    Serial.println(z);
  }
}
