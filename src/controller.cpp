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

unsigned long lastHistory = 0;

bool internet_on = false;
bool motor_force_on = false;
bool pulling_water = false;
float pool_temperature = -125;
float roof_temperature = -125;

void setupController()
{
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
}

void checkOutputs()
{
    digitalWrite(pinRelayMotor, motor_force_on || pulling_water);
    digitalWrite(pinLedMotor, motor_force_on || pulling_water);
    digitalWrite(pinLedInternet, internet_on);

    if (!internet_on)
    {
        flashPin(pinLedInternet);
    }
}

void checkDatabase()
{
    if (checkMillis(lastHistory, 10000))
    {

        Timezone myTZ;
        myTZ.setLocation(F("America/Sao_Paulo"));
        waitForSync();
        updateHistory(myTZ.tzTime(), motor_force_on, pulling_water, pool_temperature, roof_temperature);
    }
}

void runTests()
{
    test(pinLedBuiltIn, pinLedInternet, pinLedMotor, pinRelayMotor);
}
