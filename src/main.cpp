#include <Arduino.h>
#include "wifi.cpp"
#include "server.cpp"
#include "sensors.cpp"

const int LED1 = 26;
const int LED2 = 27;

void setup()
{
    Serial.begin(115200);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    setupSensors();    // Inicializa os sensores DS18B20
    configureWiFi();   // Conecta ao WiFi
    configureServer(); // Configura o servidor HTTP
}

void loop()
{
    static unsigned long lastTempReadTime = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastTempReadTime >= 5000)
    {
        lastTempReadTime = currentMillis;
        readAndPrintTemperatures(); // Lê e imprime as temperaturas a cada 5 segundos
    }

    delay(100); // Reduz o uso de CPU
}
