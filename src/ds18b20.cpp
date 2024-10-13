#include "ds18b20.h"
#include "log.h"
#include "controller.h"

// Definindo as portas dos sensores
#define ONE_WIRE_BUS_1 22
#define ONE_WIRE_BUS_2 23

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);

DallasTemperature poolSensor(&oneWire1);
DallasTemperature roofSensor(&oneWire2);

void setupDS18B20()
{
    logMessage("DS18B20", "Starting...");
    poolSensor.begin();
    roofSensor.begin();
}

float poolTemperature()
{
    poolSensor.requestTemperatures();
    return poolSensor.getTempCByIndex(0);
}

float roofTemperature()
{
    roofSensor.requestTemperatures();
    return roofSensor.getTempCByIndex(0);
}
