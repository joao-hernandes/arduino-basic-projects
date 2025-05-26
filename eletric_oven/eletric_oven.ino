#include "buttons.h"
#include "lcdmenu.h"

//Máquina de estados
enum State {
    STATE_MENU,
    STATE_TIMER,
    STATE_TEMPERATURE,
    STATE_FAN,
    STATE_SERIAL,
    STATE_RUN};
State currentState = STATE_MENU;

//Timer

//Temperatura

//LED
const byte ledPin = A5;

void setup() {
  setupButtons();                                             //Função de setup dos botões
  setupMenu();                                                //Função de setup do lcd
  pinMode(ledPin, OUTPUT);                                    //Declaração do pino do led como saida
}

void loop() {
  buttonsHandle();                                            //Função que checa flag dos botões e realiza funções especificas para cada menu

  switch (currentState) {
    case STATE_MENU:
      showMenu();
    break;

    case STATE_TIMER:
      showMenu();
    break;

    case STATE_TEMPERATURE:
      showTemp();
    break;

    case STATE_FAN:
      showMenu();
    break;

    case STATE_SERIAL:
      showMenu();
    break;

    case STATE_RUN:
      digitalWrite(ledPin, HIGH);
      showRun();
    break;
  }
}

void buttonsHandle(){
//Controle do botão "UP"
  if(flagUp){
    flagUp = false;

    if (currentState == STATE_MENU) {
      menuIndex++;
        if (menuIndex >= menuQnt) menuIndex = 0;
    }
    if(currentState == STATE_TIMER){

    }
  }

//Controle do botão "SELECT"
  if(flagSelect){
    flagSelect = false;

    if(currentState == STATE_MENU){
      currentState = static_cast<State>(menuIndex + 1);
    }

    else {currentState = STATE_MENU;} //Voltar pro menu de seleção
  }

//Controle do botão "DOWN"
  if(flagDown){
    flagDown = false;

    if (currentState == STATE_MENU) {
      menuIndex--;
      if (menuIndex < 0) menuIndex = menuQnt - 1;
    }
    
    if(currentState == STATE_TIMER){

    }
  }
}
