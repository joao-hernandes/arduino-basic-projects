#include "buttons.h"

volatile bool flagUp = false;
volatile bool flagSelect = false;
volatile bool flagDown = false;

void setupButtons(){
//Definir cada botão como entrada e resistor de pullup ligado
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
//Declarar pinos como interrupção
  attachInterrupt(digitalPinToInterrupt(buttonUp), upISR, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonSelect), selectISR, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonDown), downISR, RISING);
//Zerar flags
  flagUp = false;
  flagSelect = false;
  flagDown = false;
}

void upISR(){
  flagUp = true;
}

void selectISR(){
  flagSelect = true;
}

void downISR(){
  flagDown = true;
}