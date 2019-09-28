/* DS18B20 temperature
 * Reads temperature from waterproof sensor probe
 */
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2  // The pin that the sensor wire is connected to

const int ledPin = LED_BUILTIN;
const int threshold = 80; // Turn on the LED over 80F

OneWire oneWire(ONE_WIRE_BUS);       // Prepare the OneWire connection
DallasTemperature sensors(&oneWire); // Declare the temp sensor object

void setup(void)
{
  Serial.begin(9600);

  // Initialize the sensor
  sensors.begin();
}

void loop(void)
{ 

  sensors.requestTemperatures(); // Request a temperature reading

  // Retrieve the temperature reading in F and C
  float fahrenheit = sensors.getTempFByIndex(0);
  float celsius    = sensors.getTempCByIndex(0);

  // Display the temperature readings in a Serial Plotter-friendly format
  Serial.print("C:"); Serial.print(celsius);
  Serial.print(",");
  Serial.print("F:"); Serial.println(fahrenheit);

  if (fahrenheit > threshold){    // is the temperature over the threshold?
    digitalWrite(ledPin, HIGH);  // if it is turn on the LED
  } else {
    digitalWrite(ledPin, LOW);   // if it isn't turn the LED off
  }
  delay(1000);

}
