#include <WiFi.h>

#define TEST_MODE true // Test mode flag

// WiFi credentials
const char *ssid;
const char *password;
int wifiChannel;

void configureWiFiCredentials()
{
    if (TEST_MODE)
    {
        // Settings for Wokwi test environment
        ssid = "Wokwi-GUEST";
        password = "";   // No password for Wokwi-GUEST
        wifiChannel = 6; // Channel 6 for faster connection
    }
    else
    {
        // Settings for production environment
        ssid = "Molina_Sala";
        password = "erm55555";
        wifiChannel = 0; // Default channel
    }
}

void configureWiFi()
{
    configureWiFiCredentials();

    Serial.print("Connecting to WiFi... ");
    WiFi.mode(WIFI_STA);

    if (wifiChannel > 0)
    {
        WiFi.begin(ssid, password, wifiChannel);
    }
    else
    {
        WiFi.begin(ssid, password);
    }

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!");
        return;
    }

    Serial.println("Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
