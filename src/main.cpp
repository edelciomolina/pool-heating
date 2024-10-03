#include <Arduino.h>
#include "ds18b20.h"
#include "relay_motor.h"
#include "wifi_manager.h"
#include "firebase.h"
#include "firebase_config.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

// Configuração do NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600); // Ajuste o fuso horário (-3h para o Brasil)

void setup()
{
    Serial.begin(115200);

    setupDS18B20();  // Configura os sensores de temperatura
    setupRelay();    // Configura o relé para controlar o motor
    connectToWiFi(); // Conecta ao WiFi

    // Inicializa o cliente NTP para obter data e hora
    timeClient.begin();
    timeClient.update();

    // Configuração do Firebase usando a chave da API do firebase_config.h
    String firebaseDatabaseURL = "https://pool-heating-default-rtdb.firebaseio.com";
    setupFirebase(firebaseDatabaseURL, FIREBASE_API_KEY); // Use a chave da API do arquivo firebase_config.h
}

void loop()
{
    float temp1 = getTemperature(1); // Leitura do sensor 1
    float temp2 = getTemperature(2); // Leitura do sensor 2

    Serial.print("Temperatura do sensor 1: ");
    Serial.println(temp1);

    Serial.print("Temperatura do sensor 2: ");
    Serial.println(temp2);

    // Atualiza a data e a hora
    timeClient.update();
    String timestamp = timeClient.getFormattedTime();

    // Enviar dados para o Firebase (inclui temperatura e hora atual)
    sendTemperatureToFirebase(temp1, temp2, timestamp);

    // Controle do motor com base na temperatura
    if (temp1 > 30.0 || temp2 > 30.0)
    {
        motorOn(); // Liga o motor se qualquer sensor ultrapassar 30 graus
    }
    else
    {
        motorOff(); // Desliga o motor caso contrário
    }

    delay(5000); // Aguarda 5 segundos antes de verificar novamente
}
