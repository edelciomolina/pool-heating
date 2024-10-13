#ifndef FIREBASE_H
#define FIREBASE_H
#include <Arduino.h>
#include <HTTPClient.h>

void setupFirebase(); 
void updateHistory(bool force_motor, bool pulling_water, float pool_temperature, float roof_temperature);

#endif // FIREBASE_H
