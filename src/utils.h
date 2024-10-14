#ifndef utils_H
#define utils_H 
#include <Arduino.h>
#include <map>

boolean toggleInput(int inputPin, boolean varState, int delayTime = 500);
void flashPin(int outputPin, int times = 3, int delayTime = 100, int waitForContinueTime = 100);
bool checkMillis(unsigned long &lastMillis, unsigned long interval);

#endif // utils_H
