#ifndef TIMER1_H
#define TIMER1_H

#include <Arduino.h>

volatile extern uint8_t timerHours;
volatile extern uint8_t timerMinutes;
volatile extern uint8_t timerSeconds;

extern volatile uint8_t timerSetHours;
extern volatile uint8_t timerSetMinutes;

extern volatile bool flagCountdownOver;
extern volatile bool flagCountdownActive;

volatile extern uint8_t timerThermocouple;

void setupTimer1();
void timerStop();
void timerStart();
void timerSetCountdown();

#endif