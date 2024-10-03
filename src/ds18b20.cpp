#include "ds18b20.h"

// Definindo as portas dos sensores
#define ONE_WIRE_BUS_1 22
#define ONE_WIRE_BUS_2 23

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);

DallasTemperature sensor1(&oneWire1);
DallasTemperature sensor2(&oneWire2);

void setupDS18B20()
{
    sensor1.begin();
    sensor2.begin();
}

float getTemperature(int sensorNumber)
{
    if (sensorNumber == 1)
    {
        sensor1.requestTemperatures();
        return sensor1.getTempCByIndex(0);
    }
    else if (sensorNumber == 2)
    {
        sensor2.requestTemperatures();
        return sensor2.getTempCByIndex(0);
    }
    return -127.0; // Retorna um valor de erro se o sensor não for válido
}
