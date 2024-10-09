// #include "firebase.h"
#include "log.h"
#include "controller.h"
// #include "ds18b20.h"
// #include "wifi_manager.h"
// #include "html.h"
// #include "web_server.h"

void setup()
{
    setupLog();
    setupController();
    // setupDS18B20();
    // setupFirebase();
    // setupWiFi();
    // setupHtml();
    // setupWebServer();

    // connectToWiFi();
}

void loop()
{

    // checkInternetConnection();
    // checkPushMotor();
    // checkTemperature();
    // updateDatabase();

    test();
    delay(1000);
}
