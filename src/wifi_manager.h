#ifndef wifi_H
#define wifi_H
#include <Arduino.h>
#include <wifi.h>
#include <WiFiUdp.h>
#include <NTPClient.h> 
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

void setupWiFi();
void connectToWiFi();
void connectToWiFi(void *parameter);
void setupTimezone();
bool checkInternetConnection();
bool internetState();

extern String ip_address;
extern bool internet_connected;
extern bool test_mode; 

#endif // wifi_H
