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

#define TIME_TO_START "8:00"
#define TIME_TO_END "17:30"
#define PULL_WATER_CYCLE_CHECKER_MINUTES 15   // 15 MINUTOS
#define PULL_WATER_MANUAL_CHECKER_MINUTES 120 // 2 HORAS
#define PULL_WATER_CYCLE_TURNOFF_MINUTES 2    // 2 MINUTOS
#define DATABASE_CYCLE_SECONDS 300            // 5 MINUTOS

bool ignorePullingWatter = true;
unsigned long lastInternetCheck = 0;
unsigned long lastPullingWatterCycle = 0;
unsigned long lastPullingWatterTurnOff = 0;
unsigned long lastManualPullingWatter = 0;

bool internet_on = false;
bool motor_force_on = false;
bool pulling_water = false;
float pool_temperature = -125;
float roof_temperature = -125;
unsigned long lastDatabaseHistory = 0;

bool isOnTime()
{
    String timeNow = getTimeOfDay(myTZ.tzTime());
    return isTimeEarlier(TIME_TO_START, timeNow) && isTimeEarlier(timeNow, TIME_TO_END);
}

void setupController()
{
    pinMode(pinLedInternet, OUTPUT);
    pinMode(pinLedBuiltIn, OUTPUT);
    pinMode(pinLedMotor, OUTPUT);
    pinMode(pinRelayMotor, OUTPUT);
    pinMode(pinPushMotor, INPUT);
}

void checkInternet()
{

    if (checkMillis(lastInternetCheck, 1000 * 10))
    {

        logMessage("Controller", "Verificando conexão com internet...");

        if (!internetState())
        {
            logMessageFail();
            // xTaskCreate(connectToWiFi, "connectToWiFi", 30000, NULL, 1, NULL);
            // xTaskCreatePinnedToCore(connectToWiFi, "connectToWiFi", 8192, NULL, 1, NULL, 1);
            connectToWiFi();
        }
        else
        {
            logMessageSuccess();
        }
    }
}

void checkInputs()
{

    if (checkMillis(lastManualPullingWatter, 1000 * 60 * PULL_WATER_MANUAL_CHECKER_MINUTES))
    {
        if (motor_force_on)
        {
            motor_force_on = false;
            logMessage("Controller", "Motor em modo FORCE atingiu tempo máximo");
            return;
        }
    }

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

    if (!isOnTime())
    {
        flashPin(pinLedInternet);
    } 
}

void checkPullingWater()
{

    if (!isOnTime())
    {
        return;
    }

    if (motor_force_on)
    {
        logMessage("Controller", "Ignorado. Motor em modo FORCE");
        return;
    }

    if (checkMillis(lastPullingWatterCycle, 1000 * 60 * PULL_WATER_CYCLE_CHECKER_MINUTES))
    {
        if (ignorePullingWatter)
        {
            logMessage("Controller", "Ignorado. Primeiro cíclo automático");
            ignorePullingWatter = false;
            return;
        }

        logMessage("Controller", "Ligando motor. CYCLE_CHECKER");
        pulling_water = true;
        lastPullingWatterTurnOff = millis();
    }
    if (checkMillis(lastPullingWatterTurnOff, 1000 * 60 * PULL_WATER_CYCLE_TURNOFF_MINUTES))
    {

        logMessage("Controller", "Desligando. CYCLE_TURNOFF");
        pulling_water = false;
    }
}

void checkDatabase()
{

    if (!isOnTime())
    {
        return;
    }

    if (checkMillis(lastDatabaseHistory, 1000 * DATABASE_CYCLE_SECONDS))
    {

        unsigned long currentMillis = millis();
        unsigned long secondsPassed = (currentMillis - lastPullingWatterCycle) / 1000; // Convertendo de milissegundos para segundos
        time_t currentTime = myTZ.tzTime();
        time_t lastPullingWaterHit = currentTime - secondsPassed;

        updateHistory(myTZ.tzTime(),
                      motor_force_on,      //
                      pulling_water,       //
                      pool_temperature,    //
                      roof_temperature,    //
                      lastPullingWaterHit, //
                      test_mode,           //
                      ip_address           //
        );
    }
}

void runTests()
{
    test(pinLedBuiltIn, pinLedInternet, pinLedMotor, pinRelayMotor);
}
