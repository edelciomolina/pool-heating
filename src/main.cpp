#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include "test.h"
#include "html.h"

AsyncWebServer server(80);

HTML html;
const int LED_BUILTIN = 2;
const int LED1 = 26;
const int LED2 = 27;

bool led1State = false;
bool led2State = false;

// Note: Wokwi uses a special WiFi network called Wokwi-GUEST (no password).
// This virtual network provides internet access to the simulated ESP32.
// To learn more: https://docs.wokwi.com/guides/esp32-wifi#connecting-to-the-wifi
const char *ssid = "Molina_Sala"; // Wokwi-GUEST
const char *password = "erm55555";
// const int WIFI_CHANNEL = 6; // Speeds up the connection in Wokwi

const char *PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

String createHtml()
{
    String response = html.getControlPage();
    response.replace("LED1_TEXT", led1State ? "ON" : "OFF");
    response.replace("LED2_TEXT", led2State ? "ON" : "OFF");
    return response;
}

void piscarLED(int vezes, int intervalo)
{
    for (int i = 0; i < vezes; i++)
    {
        Serial.print("[blink]");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(intervalo);
        digitalWrite(LED_BUILTIN, LOW); // Espera um intervalo
    }
}

void setup()
{

    Serial.begin(115200);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    imprimirMensagem();

    piscarLED(3, 500);
    Serial.print("Connecting to WiFi... ");
    WiFi.mode(WIFI_STA);
    // WiFi.begin(ssid, password, WIFI_CHANNEL);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.println(" Connected!");
    piscarLED(5, 500);

    WiFi.setHostname("POOL");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { //
        if (request->hasParam("toggle"))
        {
            AsyncWebParameter *led = request->getParam("toggle");
            Serial.print("Toggle LED #");
            Serial.println(led->value());

            switch (led->value().toInt())
            {
            case 1:
                led1State = !led1State;
                digitalWrite(LED1, led1State);
                break;

            case 2:
                led2State = !led2State;
                digitalWrite(LED2, led2State);
                break;
            }
        }

        request->send(200, "text/html", createHtml());
    });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) { //
        String message;
        if (request->hasParam(PARAM_MESSAGE))
        {
            message = request->getParam(PARAM_MESSAGE)->value();
        }
        else
        {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) { //
        String message;
        if (request->hasParam(PARAM_MESSAGE, true))
        {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        }
        else
        {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

    server.begin();

    Serial.println("HTTP server started (http://localhost:8180)");
}

void loop()
{
    delay(100); // Speeds up the simulation in Wokwi
}