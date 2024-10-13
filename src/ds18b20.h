#ifndef DS18B20_H
#define DS18B20_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

void setupDS18B20();
void checkTemperature();
float poolTemperature();
float roofTemperature();

#endif // DS18B20_H
