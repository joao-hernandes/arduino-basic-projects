#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

const byte buzzerPin = A4;

volatile extern byte buzzerBips;

volatile extern bool flagBuzzer;
volatile extern bool flagBipsBuzzer;

void setupBuzzer();
void buzzerHandle();
void buzzerPlay();

#endif