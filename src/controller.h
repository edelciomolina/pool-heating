#ifndef controller_H
#define controller_H
#include <Arduino.h>

void setupController();
void motor(int state);
void ledInternet(int state);
void checkPushMotor();
int getMotorState(); 

#endif // controller_H
