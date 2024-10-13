#ifndef wifi_H
#define wifi_H
#include <Arduino.h>
#include <wifi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

void setupWiFi();
void connectToWiFi(void *parameter);
int checkInternetConnection();
bool internetState();
extern String ipAddress; 
String now();

#endif // wifi_H
