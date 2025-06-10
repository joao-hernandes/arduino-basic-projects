#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>

const byte relayPin = A0;                         //Pino do relay

volatile extern bool flagControl;

extern byte controlCounter;
extern byte controlRelayTime;

void setupControl();
void controlRelay();

#endif