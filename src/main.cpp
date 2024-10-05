#include "firebase.h"
#include "controller.h"
#include "ds18b20.h"
#include "wifi_manager.h"
#include "log.h"
#include "html.h"
#include "web_server.h"

void setup()
{

    setupLog();
    setupDS18B20();
    setupController();
    setupFirebase();
    setupWiFi();
    setupHtml();
    setupWebServer();

    connectToWiFi();
}

void loop()
{

    checkInternetConnection();
    checkPushMotor();
    checkTemperature();
    updateDatabase();

    delay(5000);
}
