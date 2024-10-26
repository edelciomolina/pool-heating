#include "wifi_manager.h"
#include "log.h"
#include "utils.h"

Timezone myTZ;
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
        logMessage("WiFi", "Configurando horário NTP...");
        myTZ.setLocation();
        myTZ.setLocation(F("America/Sao_Paulo"));

        waitForSync();
        logMessage("WiFi", myTZ.dateTime());
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
            internet_connecting = false;
            return;
        }
        else
        {
            logMessageSuccess();
        }

        ip_address = WiFi.localIP().toString();
        logMessage("WiFi", "Endereço IP: " + ip_address);

        logMessage("WiFi", "Verificando acesso a Internet...");
        if (checkInternetConnection())
        {
            logMessageSuccess();
        }
        else
        {
            logMessageFail();
        }

        setupTimezone();
    }
    catch (const std::exception &e)
    {
    }

    internet_connecting = true;
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

String getHostFromURL(const String &url, String &protocol, String &path)
{
    String host = "";

    // Detecta o protocolo (http ou https)
    int index = url.indexOf(":");
    if (index > 0)
    {
        protocol = url.substring(0, index); // Protocolo (http ou https)
    }

    // Remover o protocolo da URL
    String tempUrl = url;
    if (protocol == "http" || protocol == "https")
    {
        tempUrl = url.substring(index + 3); // Remove "http://" ou "https://"
    }

    // Separar o host e o caminho
    int pathIndex = tempUrl.indexOf("/");
    if (pathIndex > 0)
    {
        host = tempUrl.substring(0, pathIndex);
        path = tempUrl.substring(pathIndex); // Captura o caminho
    }
    else
    {
        host = tempUrl;
        path = "/";
    }

    return host;
}

String httpGET(const char *url)
{

    String payload = "";
    String protocol = "";
    String path = "";
    HTTPClient http;

    try
    {

        // Extrair host e protocolo da URL
        String host = getHostFromURL(url, protocol, path);

        if (WiFi.status() == WL_CONNECTED)
        {
            if (protocol == "http")
            {
                // Caso seja HTTP
                http.begin(host + path); // Cria a conexão HTTP

                int httpResponseCode = http.GET();
                if (httpResponseCode > 0)
                {
                    payload = http.getString();
                }

                http.end();
            }
            else if (protocol == "https")
            {
                // Caso seja HTTPS
                WiFiClientSecure client;
                client.setInsecure(); // Ignora a validação SSL

                if (client.connect(host.c_str(), 443))
                {
                    // Envia o pedido GET via HTTPS
                    client.println("GET " + path + " HTTP/1.1");
                    client.println("Host: " + host);
                    client.println("Connection: close");
                    client.println();

                    // Lê a resposta
                    while (client.connected() || client.available())
                    {
                        if (client.available())
                        {
                            payload += client.readString();
                        }
                    }

                    client.stop(); // Finaliza a conexão
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        http.end();
    }

    return payload;
}
