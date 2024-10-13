#include "firebase.h"
#include "log.h"
#include "ds18b20.h"
#include "controller.h"
#include "wifi_manager.h"
#include "firebase_config.h"

String firebaseDatabaseURL = "https://pool-heating-default-rtdb.firebaseio.com";

void setupFirebase()
{
    logMessage("Firebase", "Starting...");
}

void updateHistory(bool force_motor, bool pulling_water, float pool_temperature, float roof_temperature)
{
    if (checkInternetConnection() == WL_CONNECTED)
    {
        HTTPClient http;
        String url = firebaseDatabaseURL + "/history.json?auth=" + FIREBASE_API_KEY;

        // Preparar os dados JSON
        String jsonData = "{";
        jsonData += "\"timestamp\": \"" + now() + "\",";
        jsonData += "\"motor\": " + String(pulling_water) + ",";
        jsonData += "\"pool\": " + String(pool_temperature) + ",";
        jsonData += "\"roof\": " + String(roof_temperature);
        jsonData += "}";

        // Configura a conexão HTTP e envia a requisição POST
        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonData);

        if (httpResponseCode > 0)
        {
            logMessage("Firebase", "Dados enviados com sucesso, código de resposta: " + String(httpResponseCode));
        }
        else
        {
            logMessage("Firebase", "Erro ao enviar dados, código de erro: " + String(httpResponseCode));
        }

        http.end(); // Finaliza a conexão HTTP
    }
    else
    {
        logMessage("Firebase", "Não conectado ao WiFi");
    }
}