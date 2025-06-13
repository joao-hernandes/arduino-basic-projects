#include <stdint.h>
#include <avr/wdt.h>
#include "eletric_oven.h"
#include "timer.h"
#include "buttons.h"
#include "lcdmenu.h"
#include "temperature.h"
#include "buzzer.h"
#include "control.h"

State currentState = STATE_MENU;

void setup() {
  wdt_enable(WDTO_4S);                                        //Habilitar watchdog para reset em 4 segundos
  Serial.begin(9600);
  setupTimer1();                                              //Função de Setup do Timer 1
  setupButtons();                                             //Função de setup dos botões
  setupMenu();                                                //Função de setup do lcd
  setupTemperature();                                         //Função de setup do Sensor de temperatura
  setupControl();                                             //Função de setup do Relay
  flagSelect = false;                                         //Corrigir problema com a flag estando ativa ao iniciar o código
}

void loop() {
  wdt_reset();                                                //Reseta o watchdog
  buttonsHandle();                                            //Função que checa flag dos botões e realiza funções especificas para cada menu
  controlHandle();
  if(flagCountdownOver == true){
    currentState = STATE_END;
  }

  switch (currentState) {
    case STATE_MENU:
      showMenu();                                             //Exibe texto no LCD (lcdMenu.cpp)
    break;

    case STATE_TIMER:
      showTimer();                                            //Exibe texto no LCD (lcdMenu.cpp)
    break;
    
    case STATE_TEMPERATURE:
      showTemp();                                             //Exibe texto no LCD (lcdMenu.cpp)
    break;

    case STATE_FAN:
      showMenu();                                             //Exibe texto no LCD (lcdMenu.cpp)
    break;

    case STATE_SERIAL:
      showSerial();                                           //Exibe texto no LCD (lcdMenu.cpp)
    break;

    case STATE_RUN:
      if(!flagRun){
        showRun();                                            //Exibe texto no LCD (lcdMenu.cpp)
      }
      else{    
        showRunning();                                        //Exibe texto no LCD (lcdMenu.cpp)
      }
    break;

    case STATE_END:
      controlStop();
    break;
  }
}

void buttonsHandle(){
//Controle do botão "UP"
  if(flagUp){
    flagUp = false;                                           //Reseta a flag do botão

    if (currentState == STATE_MENU) {
      menuIndex++;                                            //Incrementa o Index do menu
        if (menuIndex >= menuQnt) menuIndex = 0;              //Se o valor do index do menu for maior ou igual a quantidade de itens no menu, zera o index
    }
    if(currentState == STATE_TIMER){
      if(timerSetMinutes < 50){
        timerSetMinutes += 10;
      }
      else{
        timerSetMinutes = 0;
        if(timerSetHours < 24){
          timerSetHours++;
        }
        else{timerSetHours = 0;}
      }
    }
    if(currentState == STATE_TEMPERATURE){
      if(temperatureSetPoint < 250){
        temperatureSetPoint += 5;
      }
      else{temperatureSetPoint = 0;}
    }
    if (currentState == STATE_RUN) {
      if(timerHours == 0 && timerMinutes == 0 && timerSeconds == 0){
        return;
      }
      flagRun = !flagRun;
    }
  }

//Controle do botão "SELECT"
  if(flagSelect){
    flagSelect = false;                                       //Reseta a flag do botão

    if(currentState == STATE_MENU){
      currentState = static_cast<State>(menuIndex + 1);
    }
    else if(currentState == STATE_TIMER){
      timerSetCountdown();                                    //Função que carrega o valor total do Timer1 (timer.cpp)
      currentState = STATE_MENU;
      timerSetHours = 0;
      timerSetMinutes = 0;
    }
    else {currentState = STATE_MENU;}                         //Voltar pro menu de seleção
  }

//Controle do botão "DOWN" NÃO FUNCIONAL
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