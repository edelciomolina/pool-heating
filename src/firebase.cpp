#include "firebase.h"
#include <WiFi.h>
#include <HTTPClient.h>

String firebaseDatabaseURL;
String firebaseApiKey;

void setupFirebase(const String& databaseURL, const String& apiKey) {
    firebaseDatabaseURL = databaseURL;
    firebaseApiKey = apiKey;
}

void sendTemperatureToFirebase(float temp1, float temp2, const String& timestamp) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = firebaseDatabaseURL + "/temperatures.json?auth=" + firebaseApiKey;

        // Preparar os dados JSON
        String jsonData = "{";
        jsonData += "\"timestamp\": \"" + timestamp + "\",";
        jsonData += "\"sensor1\": " + String(temp1) + ",";
        jsonData += "\"sensor2\": " + String(temp2);
        jsonData += "}";

        // Configura a conexão HTTP e envia a requisição POST
        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonData);

        if (httpResponseCode > 0) {
            Serial.print("Dados enviados com sucesso, código de resposta: ");
            Serial.println(httpResponseCode);
        } else {
            Serial.print("Erro ao enviar dados, código de erro: ");
            Serial.println(httpResponseCode);
        }

        http.end();  // Finaliza a conexão HTTP
    } else {
        Serial.println("Erro: Não conectado ao WiFi");
    }
}
