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

float getPoolTemperature()
{
    poolSensor.requestTemperatures();
    return poolSensor.getTempCByIndex(0);
}

float getRoofTemperature()
{
    roofSensor.requestTemperatures();
    return roofSensor.getTempCByIndex(0);
}

void checkTemperature()
{

    float poolTemperature = getPoolTemperature();
    float roofTemperature = getRoofTemperature();

    logMessage("POOL", String(poolTemperature));
    logMessage("ROOF", String(roofTemperature));

    // Controle do motor com base na temperatura
    if (roofTemperature > 30.0 || poolTemperature > 30.0)
    {
        motor(HIGH);
    }
    else
    {
        motor(LOW);
    }
}
