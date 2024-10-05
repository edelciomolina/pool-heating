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

void updateHistory(int stateMotor, float poolTemperature, float roofTemperature, const String &timestamp)
{
    if (checkInternetConnection() == WL_CONNECTED)
    {
        HTTPClient http;
        String url = firebaseDatabaseURL + "/history.json?auth=" + FIREBASE_API_KEY;

        // Preparar os dados JSON
        String jsonData = "{";
        jsonData += "\"timestamp\": \"" + timestamp + "\",";
        jsonData += "\"motor\": " + String(stateMotor) + ",";
        jsonData += "\"pool\": " + String(poolTemperature) + ",";
        jsonData += "\"roof\": " + String(roofTemperature);
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

void updateDatabase()
{

    logMessage("Firebase", "Updating...");

    String timestamp = now();
    float poolTemperature = getPoolTemperature();
    float roofTemperature = getRoofTemperature();
    int stateMotor = getMotorState();

    updateHistory(stateMotor, poolTemperature, roofTemperature, timestamp);
}
