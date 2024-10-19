#include "ds18b20.h"
#include "log.h"
#include "controller.h"

// Definindo as portas dos sensores
#define ONE_WIRE_BUS_1 23
#define ONE_WIRE_BUS_2 22

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);

DallasTemperature poolSensor(&oneWire2);
DallasTemperature roofSensor(&oneWire1);

void setupDS18B20()
{
    logMessage("DS18B20", "Starting...");
    poolSensor.begin();
    roofSensor.begin();
}

float poolTemperature()
{
    poolSensor.requestTemperatures();
    float pool_temperature = poolSensor.getTempCByIndex(0);
    return pool_temperature;
}

float roofTemperature()
{
    roofSensor.requestTemperatures();
    float roof_temperature = roofSensor.getTempCByIndex(0);
    return roof_temperature;
}
