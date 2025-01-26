#ifndef web_server_H
#define web_server_H
#include <Arduino.h>
#include <ESPAsyncWebServer.h> 
#include "ds3231.h"

void setupWebServer();
void startWebServer();

#endif // web_server_H
