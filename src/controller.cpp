#include "controller.h"
#include "log.h"

#define pinLedMotor 26
#define pinLedInternet 27
#define pinLedBuiltIn 2

#define pinPushMotor 25
#define pinRelayMotor 21

void setupController()
{

    logMessage("Controller", "Starting...");
    pinMode(pinLedInternet, OUTPUT);
    pinMode(pinLedBuiltIn, OUTPUT);
    pinMode(pinLedMotor, OUTPUT);
    pinMode(pinRelayMotor, OUTPUT);
    pinMode(pinPushMotor, INPUT);
}

void motor(int state)
{
    digitalWrite(pinLedMotor, state);
    digitalWrite(pinRelayMotor, state);
}

void ledInternet(int state)
{
    digitalWrite(pinLedInternet, state);
}

void checkPushMotor()
{
    int pushMotorState = digitalRead(pinPushMotor);
    int relayMotorState = digitalRead(pinRelayMotor);

    if (pushMotorState == HIGH)
    {

        motor(relayMotorState == HIGH ? LOW : HIGH);
        delay(500);

        while (digitalRead(pinPushMotor) == pushMotorState)
        {
        }
    }
}

int getMotorState()
{
    return digitalRead(pinPushMotor);
}

void test()
{

    logMessage("Test", "Starting...");
    delay(2000);

    logMessage("Test", "BuiltIn Led...");
    digitalWrite(pinLedBuiltIn, HIGH);
    delay(2000);
    digitalWrite(pinLedBuiltIn, LOW);

    logMessage("Test", "Internet Led...");
    digitalWrite(pinLedInternet, HIGH);
    delay(2000);
    digitalWrite(pinLedInternet, LOW);

    logMessage("Test", "Motor Led...");
    digitalWrite(pinLedMotor, HIGH);
    delay(2000);
    digitalWrite(pinLedMotor, LOW);

    logMessage("Test", "Motor Relay...");
    digitalWrite(pinRelayMotor, HIGH);
    delay(2000);
    digitalWrite(pinRelayMotor, LOW);
}