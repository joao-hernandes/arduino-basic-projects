#ifndef TIMER1_H
#define TIMER1_H

#include <Arduino.h>

volatile extern byte hours;
volatile extern byte minutes;
volatile extern byte seconds;

extern volatile byte setHours;
extern volatile byte setMinutes;

extern volatile bool countdownOver;

void setupTimer1();
void timerStop();
void timerStart();
void timerSetCountdown();

#endif