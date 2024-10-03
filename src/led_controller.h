#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

// Definir o LED_BUILTIN se ele não estiver definido
#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // Pino 2 para o LED embutido no ESP32
#endif

void setupLEDs();
void toggleLED(int ledNumber);
String getLEDStatus(int ledNumber);
void piscarLED(int vezes, int intervalo);

#endif // LED_CONTROLLER_H
