#include "log.h"

void setupLog()
{
    
    logMessage("Log", "Starting...");
    Serial.begin(115200);
}

void logMessage(const String &label, const String &message)
{
    Serial.print("[");
    Serial.print(label);
    Serial.print("] ");
    Serial.println(message);
}

void logValue(const String &label, int value)
{
    Serial.print("[");
    Serial.print(label);
    Serial.print("] ");
    Serial.println(value);
}

void logValue(const String &label, float value)
{
    Serial.print("[");
    Serial.print(label);
    Serial.print("] ");
    Serial.println(value, 2);  
}