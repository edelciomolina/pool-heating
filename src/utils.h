#ifndef utils_H
#define utils_H
#include <Arduino.h>
#include <map>

boolean toggleInput(int inputPin, boolean varState, int delayTime = 500);
void flashPin(int outputPin, int times = 3, int delayTime = 100, int waitForContinueTime = 100);
bool checkMillis(unsigned long &lastMillis, unsigned long interval);

String timestampToDateTime(time_t timestamp);
time_t dateTimeToTimestamp(String datetime);
String getTimeOfDay(time_t timestamp);
bool isTimeEarlier(String time1, String time2);
String httpGET(const char *serverName);
String jsonGET(const char *url, const char *fieldName);
bool isValidDateTime(String datetime);

#endif // utils_H
