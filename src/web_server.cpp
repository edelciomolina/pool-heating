
#include "web_server.h"
#include "wifi_manager.h"
#include "log.h"
#include "html.h"
#include "controller.h"

AsyncWebServer server(80);
// const char *PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

String createHtml()
{
    String response = getControlPage();
    // response.replace("LED1_TEXT", getLEDStatus(1));
    // response.replace("LED2_TEXT", getLEDStatus(2));
    return response;
}

void setupWebServer()
{
    logMessage("WebServer", "Starting...");
    startWebServer();
}

void startWebServer()
{
    // setupLEDs();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { //
        // if (request->hasParam("motor"))
        // {
        //      toggleMotor();
        // }
        // if (request->hasParam("toggle"))
        // {
        //     AsyncWebParameter *led = request->getParam("toggle");
        //      toggleLED(led->value().toInt());
        // }
        request->send(200, "text/html", createHtml());
    });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) { //
        // String message;
        // if (request->hasParam(PARAM_MESSAGE))
        // {
        //     message = request->getParam(PARAM_MESSAGE)->value();
        // }
        // else
        // {
        //     message = "No message sent";
        // }
        // request->send(200, "text/plain", "Hello, GET: " + message);
    });

    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) { //
        String result = "";
        String name = request->getParam("name", true)->value();
        String value = request->getParam("value", true)->value();

        if (name == "motor")
        {
            if (value == "toggle")
            {
                result = toggleMotor();
            }
        }

        // Cria a string JSON manualmente
        String response = "{";
        response += "\"name\":\"" + name + "\",";
        response += "\"value\":\"" + value + "\",";
        response += "\"result\":\"" + result + "\"";
        response += "}";

        // Envia a resposta como JSON
        request->send(200, "application/json", response);

    });

    server.onNotFound(notFound);
    server.begin();
    logMessage("WebServer", "HTTP server started (http://" + ip_address + ":8180)");
}
