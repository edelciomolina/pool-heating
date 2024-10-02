#include <DallasTemperature.h>
#include <OneWire.h>

// Pin definitions
const int SENSOR1_PIN = 22;
const int SENSOR2_PIN = 23;

// DS18B20 temperature sensor setup
OneWire oneWire1(SENSOR1_PIN);
OneWire oneWire2(SENSOR2_PIN);
DallasTemperature sensor1(&oneWire1);
DallasTemperature sensor2(&oneWire2);

void setupSensors()
{
    sensor1.begin();
    sensor2.begin();
}

void readAndPrintTemperatures()
{
    sensor1.requestTemperatures();
    sensor2.requestTemperatures();

    float temp1 = sensor1.getTempCByIndex(0);
    float temp2 = sensor2.getTempCByIndex(0);

    Serial.print("Sensor 1 Temperature: ");
    Serial.print(temp1);
    Serial.println(" °C");

    Serial.print("Sensor 2 Temperature: ");
    Serial.print(temp2);
    Serial.println(" °C");
}
