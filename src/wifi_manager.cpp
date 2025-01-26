#include "wifi_manager.h"
#include "ds3231.h"
#include "log.h"
#include "utils.h"

bool internet_connecting = false;
bool internet_connected = false;
bool test_mode = false;
const char *ssid = "Molina_Sala";
const char *password = "erm55555";
// const char *ssid = "UaiFi";
// const char *password = "123456789m";
String ip_address = "127.0.0.1";

void setupWiFi()
{
    logMessage("WiFi", "Starting...");
    connectToWiFi();
}

void setupTimezone()
{
    if (checkInternetConnection())
    {
        setupTime_DS3231();
    }
}

void connectToWiFi(void *parameter)
{
    connectToWiFi();
}

void connectToWiFi()
{
    try
    {

        if (internet_connecting)
            return;

        internet_connecting = true;

        WiFi.disconnect();
        WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, IPAddress(8, 8, 8, 8));

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

        delay(3000);
        if (WiFi.status() != WL_CONNECTED)
        {
            logMessageFail();
        }
        else
        {

            logMessageSuccess();

            ip_address = WiFi.localIP().toString();
            logMessage("WiFi", "Endereço IP: " + ip_address);

            logMessage("WiFi", "Verificando acesso a Internet...");
            if (checkInternetConnection())
            {
                logMessageSuccess();
                setupTimezone();
            }
            else
            {
                logMessageFail();
            }
        }
    }
    catch (const std::exception &e)
    {
    }

    internet_connecting = false;
}

bool checkInternetConnection()
{
    internet_connected = (httpGET("https://checkip.amazonaws.com").length() > 0);
    return internet_connected;
}

bool internetState()
{
    return internet_connected;
}
