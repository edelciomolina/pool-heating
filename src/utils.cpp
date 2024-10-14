#include "utils.h"

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