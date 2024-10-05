#ifndef DS18B20_H
#define DS18B20_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

void setupDS18B20();
void checkTemperature();
float getPoolTemperature();
float getRoofTemperature();

#endif // DS18B20_H
