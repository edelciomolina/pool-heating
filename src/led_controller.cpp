#include "led_controller.h"

int led1Pin = 26;
int led2Pin = 27;
bool led1State = false;
bool led2State = false;

void setupLEDs()
{
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void toggleLED(int ledNumber)
{
    if (ledNumber == 1)
    {
        led1State = !led1State;
        digitalWrite(led1Pin, led1State);
    }
    else if (ledNumber == 2)
    {
        led2State = !led2State;
        digitalWrite(led2Pin, led2State);
    }
}

String getLEDStatus(int ledNumber)
{
    if (ledNumber == 1)
    {
        return led1State ? "ON" : "OFF";
    }
    else if (ledNumber == 2)
    {
        return led2State ? "ON" : "OFF";
    }
    return "UNKNOWN";
}

void piscarLED(int vezes, int intervalo)
{
    for (int i = 0; i < vezes; i++)
    {
        Serial.print("[blink]");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(intervalo);
        digitalWrite(LED_BUILTIN, LOW);
        delay(intervalo);
    }
}
