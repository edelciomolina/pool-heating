#include "wifi_manager.h"
#include "controller.h"
#include "log.h"

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
    timeClient.begin();
    timeClient.update();
}

void connectToWiFi()
{ 
    if (testMode)
    {
        logMessage("WiFi", "Conectando no modo de teste...");
        WiFi.begin("Wokwi-GUEST", "", 6); // Canal 6
    }
    else
    {
        logMessage("WiFi", "Conectando no modo normal...");
        WiFi.begin(ssid, password, 0); // Canal 0
    }
 
    int maxRetries = 10; 
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < maxRetries)
    {
        delay(1000);
        logMessage("WiFi", "Tentativa " + String(retries));
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        ipAddress = WiFi.localIP().toString();
        logMessage("WiFi", "Conectado ao WiFi!");
        logMessage("WiFi", "Endereço IP: " + ipAddress);
    }
    else
    {
        logMessage("WiFi", "Falha na conexão WiFi!");
    }
}

int checkInternetConnection()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        // Tenta conectar ao servidor 8.8.8.8 (Google DNS) na porta 80
        if (client.connect("8.8.8.8", 80))
        {
            ledInternet(HIGH);
            client.stop();
        }
        else
        {
            ledInternet(LOW);
        }
    }
    else
    {
        ledInternet(LOW);
        return 0;
    }
    return WiFi.status();
}

String now()
{

    timeClient.update();
    return timeClient.getFormattedTime();
}