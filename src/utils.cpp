#include "utils.h"
#include <ctime>

std::map<int, unsigned long> lastExecutionMap;

bool toggleInput(int inputPin, bool varState, int delayTime)
{
    int pushMotorState = digitalRead(inputPin);

    if (pushMotorState == HIGH)
    {
        varState = !varState;

        while (digitalRead(inputPin) == pushMotorState)
        {
        }

        delay(delayTime);
    }

    return varState;
}

void flashPin(int outputPin, int times, int delayTime, int waitForContinueTime)
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(outputPin, HIGH);
        delay(delayTime);
        digitalWrite(outputPin, LOW);
        delay(delayTime);
    }
    delay(waitForContinueTime);
}

bool checkMillis(unsigned long &lastMillis, unsigned long interval)
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastMillis >= interval || lastMillis == 0)
    {
        lastMillis = currentMillis;
        return true;
    }

    return false;
}

String timestampToDateTime(time_t timestamp)
{
    struct tm *timeinfo;
    char buffer[20];
    timeinfo = std::localtime(&timestamp);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return String(buffer);
}

time_t dateTimeToTimestamp(String datetime)
{
    struct tm tm;
    if (sscanf(datetime.c_str(), "%d-%d-%d %d:%d:%d", //
               &tm.tm_year, &tm.tm_mon, &tm.tm_mday,  //
               &tm.tm_hour, &tm.tm_min, &tm.tm_sec    //
               ) == 6                                 //
    )
    {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_isdst = -1;
        return mktime(&tm);
    }
    return -1;
}

String getTimeOfDay(time_t timestamp)
{
    struct tm *timeinfo;
    char buffer[9];
    timeinfo = std::localtime(&timestamp);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    return String(buffer);
}

bool isTimeEarlier(String time1, String time2)
{
    int hour1, minute1;
    int hour2, minute2;

    sscanf(time1.c_str(), "%d:%d", &hour1, &minute1);
    sscanf(time2.c_str(), "%d:%d", &hour2, &minute2);

    if (hour1 < hour2)
    {
        return true;
    }
    else if (hour1 > hour2)
    {
        return false;
    }
    else
    {
        return minute1 < minute2;
    }
}