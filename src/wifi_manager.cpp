#include "wifi_manager.h"
#include "log.h"

bool internet_connected = false;
bool testMode = true;
const char *ssid = "Molina_Sala";
const char *password = "erm55555";
String ipAddress = "127.0.0.1";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600);

void setupWiFi()
{
    logMessage("WiFi", "Starting...");

    connectToWiFi(NULL);

    // xTaskCreate(
    //     connectToWiFi,   // Função que será chamada
    //     "connectToWiFi", // Nome da task (para fins de debug)
    //     10000,           // Tamanho da stack (em bytes)
    //     NULL,            // Parâmetro para a função (não usado aqui)
    //     1,               // Prioridade da task (1 é a prioridade normal)
    //     NULL             // Handle da task (não usado aqui)
    // );
}

void connectToWiFi(void *parameter)
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

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    ipAddress = WiFi.localIP().toString();
    logMessage("WiFi", "Conectado a rede WiFi!");
    logMessage("WiFi", "Endereço IP: " + ipAddress);

    logMessage("WiFi", "Verificando acesso a Internet...");
    checkInternetConnection();

}

int checkInternetConnection()
{

    timeClient.begin();
    timeClient.update();
    internet_connected = timeClient.getEpochTime() != 0;

    if (internet_connected)
    {
        logMessage("WiFi", "Internet OK! " + now());
    }
    else
    {
        logMessage("WiFi", "Internet  FAIL!");
    }

    return internet_connected;
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