#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>

extern const uint8_t relayPin;                         //Pino do relay
extern const uint8_t ledPin;

extern bool firstStopRun;
extern bool firstRun;

volatile extern bool flagControl;

extern uint8_t controlCounter;
extern uint8_t controlRelayTime;

void setupControl();
void controlRelay();
void controlHandle();
void peripheralsStop();
void controlStop();

#endif