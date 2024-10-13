#ifndef SERIAL_LOGGER_H
#define SERIAL_LOGGER_H
#include <Arduino.h>

void logMessage(const String &label, const String &message);
void logValue(const String &label, int value);
void logValue(const String &label, float value);
void setupLog();

#endif // SERIAL_LOGGER_H
