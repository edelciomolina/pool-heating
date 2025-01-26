#include "log.h"
#include "controller.h"
#include "ds18b20.h"
#include "ds3231.h"
#include "wifi_manager.h"
#include "firebase.h"
#include "utils.h"
// #include "html.h"
// #include "web_server.h"

void setup()
{
    delay(1000);
    setupDS3231();
    setupDS18B20();
    setupLog();
    setupController();

    setupWiFi();
    setupFirebase();
    // setupHtml();
    // setupWebServer();
}

void loop()
{

    checkInternet();
    checkInputs();
    checkDatabase();
    checkPullingWater();
    checkOutputs();

    Serial.print(".");
    delay(100); 
}
