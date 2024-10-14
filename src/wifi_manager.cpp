#include "wifi_manager.h"
#include "log.h"

bool internet_connecting = false;
bool internet_connected = false;
bool testMode = true;
const char *ssid = "Molina_Sala";
const char *password = "erm55555";
String ipAddress = "127.0.0.1";

void setupWiFi()
{
    logMessage("WiFi", "Starting...");
    connectToWiFi();
    setupTimezone();
}

void setupTimezone()
{
    if (checkInternetConnection())
    {
        logMessage("WiFi", "Configurando horário NTP...");
        Timezone myTZ;
        if (!myTZ.setLocation(F("America/Sao_Paulo")))
        {
            myTZ.setLocation();
        }
        waitForSync();
        logMessage("WiFi", myTZ.dateTime());
    }
}

void connectToWiFi()
{
    if (internet_connecting)
        return;

    internet_connecting = true;

    if (testMode)
    {
        logMessage("WiFi", "Conectando em Wokwi-GUEST...");
        WiFi.begin("Wokwi-GUEST", "", 6); // Canal 6
    }
    else
    {
        logMessage("WiFi", "Conectando no modem WIFI...");
        WiFi.begin(ssid, password, 0); // Canal 0
    }

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    ipAddress = WiFi.localIP().toString();
    logMessage("WiFi", "Conectado a rede WiFi!");
    logMessage("WiFi", "Endereço IP: " + ipAddress);

    logMessage("WiFi", "Verificando acesso a Internet...");
    if (checkInternetConnection())
    {
        logMessage("WiFi", "Internet OK!");
    }
    else
    {
        logMessage("WiFi", "Internet  FAIL!");
    }

    internet_connecting = true;
}

bool checkInternetConnection()
{
    internet_connected = true; // TODO Resolver isso!!!
    return internet_connected;
}

bool internetState()
{
    return internet_connected;
}