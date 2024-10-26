#include "log.h"
#include "utils.h"
#include "wifi_manager.h"

void setupLog()
{
    logMessage("Log", "Starting...");
    Serial.begin(115200);
}

void logSkipLine()
{
    Serial.println();
}


void logMessage(const String &label, const String &message, const bool &skipLineAtEnd)
{
    String timeNow = getTimeOfDay(myTZ.tzTime());
    if (!skipLineAtEnd)
    {
        Serial.println();
    }

    if(label.length() > 0)
    {
        Serial.print(timeNow);
        Serial.print(" [");
        Serial.print(label);
        Serial.print("] ");
    }

    Serial.print(message);

    if (skipLineAtEnd)
    {
        Serial.println();
    }
}

void logMessageSuccess()
{
    logMessage("", " (OK)", true);
}

void logMessageFail()
{
    logMessage("", " (FAILED)", true);
}

void logMessage(const String &message)
{
    logMessage("", message, false);
}


void logMessage(const String &message, const bool &ignoreLn)
{
    logMessage("", message, ignoreLn);
}


void logMessage(const String &label, const String &message)
{
    logMessage(label, message, false);
}

void logValue(const String &label, int value)
{
    logMessage(label, String(value), false);
}

void logValue(const String &label, int value, const bool &ignoreLn)
{
    logMessage(label, String(value), ignoreLn);
}

void logValue(const String &label, float value)
{
    String formattedValue = String(value, 2);
    logMessage(label, formattedValue, false);
}

void logValue(const String &label, float value, const bool &ignoreLn)
{
    String formattedValue = String(value, 2);
    logMessage(label, formattedValue, false);
}