#include "wifi_manager.h"
#include "log.h"

bool internet_connected = false;
bool testMode = true;
const char *ssid = "Molina_Sala";
const char *password = "erm55555";
String ipAddress = "127.0.0.1";

WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600);

void setupWiFi()
{
    logMessage("WiFi", "Starting...");
}

void connectToWiFi()
{
 
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

    delay(1000);

    if (WiFi.status() == WL_CONNECTED)
    {
        ipAddress = WiFi.localIP().toString();
        logMessage("WiFi", "Conectado a rede WiFi!");
        logMessage("WiFi", "Endereço IP: " + ipAddress);
    }
    else
    {
        logMessage("WiFi", "Falha na conexão com o Modem WiFi!");
        logMessage("WiFi", "Tentando reconectar...");
        connectToWiFi();
    }
}

void tryToReconnect()
{

    if (checkInternetConnection() == WL_CONNECTED)
    {
        logMessage("WiFi", "Conectado a internet!");

        timeClient.begin();
        timeClient.update();
        logMessage("WiFi", "NTP conectado e atualizado!");
    }
    else
    {
        connectToWiFi();
    }
}

int checkInternetConnection()
{
    logMessage("WiFi", "Verificando conexão com a internet...");
    if (WiFi.status() == WL_CONNECTED)
    {
        // Tenta conectar ao servidor 8.8.8.8 (Google DNS) na porta 80
        if (client.connect("8.8.8.8", 80))
        {

            logMessage("WiFi", "Ping 8.8.8.8 OK!");

            internet_connected = true;
            client.stop();
        }
        else
        {

            logMessage("WiFi", "Ping 8.8.8.8 FAIL!");

            internet_connected = false;
        }
    }
    else
    {
        internet_connected = false;
        return 0;
    }
    return WiFi.status();
}

String now()
{

    timeClient.update();
    return timeClient.getFormattedTime();
}

bool internetState()
{
    return internet_connected;
}