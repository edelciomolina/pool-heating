#include "log.h"
#include "controller.h"
#include "ds18b20.h"
#include "wifi_manager.h"
#include "firebase.h"
#include "utils.h"
// #include "html.h"
// #include "web_server.h"

void setup()
{
    setupLog();
    setupDS18B20();
    setupController();

    setupWiFi();
    setupFirebase();
    // setupHtml();
    // setupWebServer();
}

void loop()
{

    checkInputs();
    checkOutputs();
    checkDatabase();

    Serial.print(".");
    delay(100); 
}
