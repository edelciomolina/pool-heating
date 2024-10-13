#include "test.h"
#include "log.h"
#include "controller.h"

void test(int pinLedBuiltIn, int pinLedInternet, int pinLedMotor, int pinRelayMotor)
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