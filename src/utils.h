#ifndef utils_H
#define utils_H
#include <Arduino.h>
 
boolean toggleInput(int inputPin, boolean varState, int delayTime = 500);
void flashPin(int outputPin, int times = 3, int delayTime = 100, int waitForContinueTime = 100);

#endif // utils_H
