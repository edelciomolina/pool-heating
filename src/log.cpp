#include "log.h"

void setupLog()
{
    logMessage("Log", "Starting...");
    Serial.begin(115200);
}

void logSkipLine()
{
    Serial.println();
}

void logMessage(const String &label, const String &message)
{
    Serial.println();
    Serial.print("[");
    Serial.print(label);
    Serial.print("] ");
    Serial.print(message);
}

void logValue(const String &label, int value)
{
    Serial.println();
    Serial.print("[");
    Serial.print(label);
    Serial.print("] ");
    Serial.print(value);
}

void logValue(const String &label, float value)
{
    Serial.println();
    Serial.print("[");
    Serial.print(label);
    Serial.print("] ");
    Serial.print(value, 2);
}