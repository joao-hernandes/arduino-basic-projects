#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

//Pino dos botões
const byte buttonUp = 2;
const byte buttonSelect = 3;
const byte buttonDown = 4;

//Flag para controle de interrupção
extern volatile bool flagUp;
extern volatile bool flagSelect;
extern volatile bool flagDown;

//Funções de Setup
void setupButtons();
void buttonsHandle();

//Funções de Interrupção
void upISR();
void selectISR();
void downISR();

#endif