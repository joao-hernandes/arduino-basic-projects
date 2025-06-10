#ifndef TIMER1_H
#define TIMER1_H

#include <Arduino.h>

volatile extern byte timerHours;
volatile extern byte timerMinutes;
volatile extern byte timerSeconds;

extern volatile byte timerSetHours;
extern volatile byte timerSetMinutes;

extern volatile bool flagCountdownOver;

volatile extern byte timerThermocouple;

void setupTimer1();
void timerStop();
void timerStart();
void timerSetCountdown();

#endif