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
  EIMSK |= (1 << INT0)  | (1 << INT1);                                        //Habilita interrupção externa INT0 e INT1
  EICRA |= (1 << ISC01) | (1 << ISC00);                                       //INT0 borda de subida
  EICRA |= (1 << ISC11) | (1 << ISC10);                                       //INT1 borda de subida

  //attachInterrupt(digitalPinToInterrupt(buttonUp), upISR, RISING);
  //attachInterrupt(digitalPinToInterrupt(buttonSelect), selectISR, RISING);
  //attachInterrupt(digitalPinToInterrupt(buttonDown), downISR, RISING);
//Zerar flags
  flagUp = false;
  flagSelect = false;
  flagDown = false;
}

ISR(INT0_vect){
  flagUp = true;
}

ISR(INT1_vect){
  flagSelect = true;
}

void downISR(){
  flagDown = true;
}