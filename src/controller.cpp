#include "controller.h"
#include "wifi_manager.h"
#include "firebase.h"
#include "ds18b20.h"
#include "utils.h"
#include "log.h"
#include "test.h"

#define pinLedMotor 26
#define pinLedInternet 27
#define pinLedBuiltIn 2

#define pinPushMotor 25
#define pinRelayMotor 21

bool internet_on = false;
bool motor_force_on = false;
bool pulling_water = false;
bool pool_temperature = -125;
bool roof_temperature = -125;

void setupController()
{

    logMessage("Controller", "Starting...");
    pinMode(pinLedInternet, OUTPUT);
    pinMode(pinLedBuiltIn, OUTPUT);
    pinMode(pinLedMotor, OUTPUT);
    pinMode(pinRelayMotor, OUTPUT);
    pinMode(pinPushMotor, INPUT);
}

void checkInputs()
{
    pool_temperature = poolTemperature();
    roof_temperature = roofTemperature();
    motor_force_on = toggleInput(pinPushMotor, motor_force_on);
    internet_on = internetState();

    String mesage = String(pulling_water) + " " +
                    String(motor_force_on) + " " +
                    String(internet_on);

    logMessage("Controller", mesage);
}

void checkChanges()
{
    digitalWrite(pinRelayMotor, motor_force_on || pulling_water);
    digitalWrite(pinLedMotor, motor_force_on || pulling_water);
    digitalWrite(pinLedInternet, internet_on);

    if (!internet_on)
    {
        flashPin(pinLedInternet);
        tryToReconnect();
    }

    // updateHistory(motor_force_on, pulling_water, pool_temperature, roof_temperature);
}

void runTests()
{
    test(pinLedBuiltIn, pinLedInternet, pinLedMotor, pinRelayMotor);
}
