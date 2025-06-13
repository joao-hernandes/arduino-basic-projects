#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

//Pino dos botões
const uint8_t buttonUp = 2;
const uint8_t buttonSelect = 3;
const uint8_t buttonDown = 4;

//Flag para controle de interrupção
extern volatile bool flagUp;
extern volatile bool flagSelect;
extern volatile bool flagDown;

//Flag para controle do Menu Run
extern volatile bool flagRun;


//Funções de Setup
void setupButtons();
void buttonsHandle();

//Funções de Interrupção
void upISR();
void selectISR();
void downISR();

#endif