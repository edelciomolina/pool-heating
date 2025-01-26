#include "utils.h"
#include <HTTPClient.h>
#include <ctime>

std::map<int, unsigned long> lastExecutionMap;

bool toggleInput(int inputPin, bool varState, int delayTime)
{
    int pushMotorState = digitalRead(inputPin);

    if (pushMotorState == HIGH)
    {
        varState = !varState;

        while (digitalRead(inputPin) == pushMotorState)
        {
        }

        delay(delayTime);
    }

    return varState;
}

void flashPin(int outputPin, int times, int delayTime, int waitForContinueTime)
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(outputPin, HIGH);
        delay(delayTime);
        digitalWrite(outputPin, LOW);
        delay(delayTime);
    }
    delay(waitForContinueTime);
}

bool checkMillis(unsigned long &lastMillis, unsigned long interval)
{
    unsigned long currentMillis = millis();
    unsigned long securityMarginMs = 5000; // 5 segundos de segurança
    if (currentMillis - lastMillis >= interval + securityMarginMs || lastMillis == 0)
    {
        lastMillis = currentMillis;
        return true;
    }

    return false;
}

String timestampToDateTime(time_t timestamp)
{
    struct tm *timeinfo;
    char buffer[20];
    timeinfo = std::localtime(&timestamp);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return String(buffer);
}

time_t dateTimeToTimestamp(String datetime)
{
    struct tm tm;
    if (sscanf(datetime.c_str(), "%d-%d-%d %d:%d:%d", //
               &tm.tm_year, &tm.tm_mon, &tm.tm_mday,  //
               &tm.tm_hour, &tm.tm_min, &tm.tm_sec    //
               ) == 6                                 //
    )
    {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_isdst = -1;
        return mktime(&tm);
    }
    return -1;
}

String getTimeOfDay(time_t timestamp)
{
    struct tm *timeinfo;
    char buffer[9];
    timeinfo = std::localtime(&timestamp);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    return String(buffer);
}

bool isTimeEarlier(String time1, String time2)
{
    int hour1, minute1;
    int hour2, minute2;

    sscanf(time1.c_str(), "%d:%d", &hour1, &minute1);
    sscanf(time2.c_str(), "%d:%d", &hour2, &minute2);

    if (hour1 < hour2)
    {
        return true;
    }
    else if (hour1 > hour2)
    {
        return false;
    }
    else
    {
        return minute1 < minute2;
    }
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

String jsonGET(const char *url, const char *fieldName)
{
    // Obtém o JSON bruto da URL
    String jsonResponse = httpGET(url);

    // Verifica se a resposta está vazia
    if (jsonResponse.length() == 0)
    {
        return "Erro: Resposta vazia ou erro de conexão";
    }

    // Constrói o padrão do campo a ser buscado
    String fieldPattern = String("\"") + fieldName + "\":\"";

    // Encontra a posição inicial do campo
    int fieldStart = jsonResponse.indexOf(fieldPattern);
    if (fieldStart == -1)
    {
        return "Erro: Campo não encontrado no JSON";
    }

    // Move o índice para o início do valor
    fieldStart += fieldPattern.length();

    // Encontra a posição final do valor (fechamento das aspas)
    int fieldEnd = jsonResponse.indexOf("\"", fieldStart);
    if (fieldEnd == -1)
    {
        return "Erro: Valor do campo está incompleto";
    }

    // Extrai e retorna o valor do campo
    return jsonResponse.substring(fieldStart, fieldEnd);
}

bool isValidDateTime(String datetime)
{

    // Remove os milissegundos, se existirem (parte após o '.')
    int dotIndex = datetime.indexOf('.');
    if (dotIndex != -1)
    {
        datetime = datetime.substring(0, dotIndex);
    }

    // Verifica se o comprimento é exato (19 caracteres)
    if (datetime.length() != 19)
    {
        return false;
    }

    // Verifica se existe o caractere 'T' na posição 10
    if (datetime[10] != 'T')
    {
        return false;
    }

    return true; // Passou nas verificações
}
