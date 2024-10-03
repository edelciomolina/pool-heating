#include "relay_motor.h"

// Definir a porta do relé
#define RELAY_PIN 21

void setupRelay()
{
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Garante que o motor esteja desligado no início
}

void motorOn()
{
    digitalWrite(RELAY_PIN, HIGH); // Liga o motor
}

void motorOff()
{
    digitalWrite(RELAY_PIN, LOW); // Desliga o motor
}
