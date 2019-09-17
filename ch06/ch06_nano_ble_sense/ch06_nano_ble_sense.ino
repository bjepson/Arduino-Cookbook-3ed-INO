#include <Arduino_APDS9960.h>
#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_LSM9DS1.h>

void setup() {
  
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
    while (1);
  }
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  prompt();
}

void prompt() {
  Serial.println("Swipe!");
  Serial.println("Up for temperature, down for humidity");
  Serial.println("Left for pressure, right for gyro fun.");
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
    Serial.print(x); Serial.print(' ');
    Serial.print(y); Serial.print(' ');
    Serial.println(z);
  }
}
void loop() {
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
        Serial.println("Spin me right round\nx y z");
        for (int i = 0; i < 10; i++)
        {
          readGyro();
          delay(100);
        }
        break;

      default:
        break;
    }
    prompt();
  }
}
