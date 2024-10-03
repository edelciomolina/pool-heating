#include "wifi_manager.h"
#include <WiFi.h>

const char *ssid = "Molina_Sala";
const char *password = "erm55555";

void connectToWiFi()
{
    if (WiFi.begin(ssid, password) != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!");
        return;
    }
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
