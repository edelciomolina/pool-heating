#ifndef controller_H
#define controller_H
#include <Arduino.h>

void runTests();
void setupController();
void checkInternet();
void checkInputs();
void checkOutputs();
void checkDatabase();
void checkPullingWater(); 
bool toggleMotor();
#endif // controller_H
