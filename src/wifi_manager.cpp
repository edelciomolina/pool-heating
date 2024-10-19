#include "wifi_manager.h"
#include "log.h"

Timezone myTZ;
bool internet_connecting = false;
bool internet_connected = false;
bool test_mode = false;
const char *ssid = "Molina_Sala";
const char *password = "erm55555";
String ip_address = "127.0.0.1";

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
        myTZ.setLocation();
        myTZ.setLocation(F("America/Sao_Paulo"));

        waitForSync();
        logMessage("WiFi", myTZ.dateTime());
    }
}

void connectToWiFi()
{
    if (internet_connecting)
        return;

    internet_connecting = true;

    if (test_mode)
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

    ip_address = WiFi.localIP().toString();
    logMessage("WiFi", "Conectado a rede WiFi!");
    logMessage("WiFi", "Endereço IP: " + ip_address);

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