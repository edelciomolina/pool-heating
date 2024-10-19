#ifndef wifi_H
#define wifi_H
#include <Arduino.h>
#include <wifi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ezTime.h>

void setupWiFi(); 
void connectToWiFi();
void setupTimezone();
bool checkInternetConnection();
bool internetState();
 
extern String ip_address; 
extern bool internet_connected; 
extern bool test_mode; 
extern Timezone myTZ;

#endif // wifi_H
