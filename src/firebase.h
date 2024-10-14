#ifndef FIREBASE_H
#define FIREBASE_H
#include <Arduino.h>
#include <HTTPClient.h> 
#include <WiFi.h>
#include <FirebaseESP32.h>

void setupFirebase(); 
void updateHistory(time_t timestamp, bool force_motor, bool pulling_water, float pool_temperature, float roof_temperature);
String timestampToDateTime(time_t timestamp);

#endif // FIREBASE_H
