#ifndef SERIAL_LOGGER_H
#define SERIAL_LOGGER_H
#include <Arduino.h>

void setupLog();

void logMessageSuccess();
void logMessageFail();
void logMessage(const String &message);
void logMessage(const String &label, const String &message);
void logMessage(const String &label, const String &message, const bool &ignoreLn);
void logValue(const String &label, int value);
void logValue(const String &label, int value, const bool &ignoreLn);
void logValue(const String &label, float value);
void logValue(const String &label, float value, const bool &ignoreLn);
void logSkipLine();

#endif // SERIAL_LOGGER_H
