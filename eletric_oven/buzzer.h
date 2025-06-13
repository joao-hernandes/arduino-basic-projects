#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

const uint8_t buzzerPin = A4;

volatile extern uint8_t buzzerBips;

volatile extern bool flagBuzzer;
volatile extern bool flagBipsBuzzer;

void setupBuzzer();
void buzzerHandle();
void buzzerPlay();

#endif