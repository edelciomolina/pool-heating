#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

bool led1State = false;
bool led2State = false;

void toggleLED(int ledNumber)
{
    switch (ledNumber)
    {
    case 1:
        led1State = !led1State;
        digitalWrite(26, led1State);
        break;
    case 2:
        led2State = !led2State;
        digitalWrite(27, led2State);
        break;
    }
}

void configureServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("toggle")) {
            int ledNumber = request->getParam("toggle")->value().toInt();
            toggleLED(ledNumber);
        }
        request->send(200, "text/html", "LED toggled"); });

    server.begin();
    Serial.println("HTTP server started");
}
