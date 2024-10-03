#ifndef FIREBASE_H
#define FIREBASE_H

#include <Arduino.h>

void setupFirebase(const String &databaseURL, const String &apiKey);
void sendTemperatureToFirebase(float temp1, float temp2);

#endif // FIREBASE_H
