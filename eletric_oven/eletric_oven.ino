#include "timer.h"
#include "buttons.h"
#include "lcdmenu.h"
#include "temperature.h"
#include "buzzer.h"

//Máquina de estados
enum State {
    STATE_MENU,
    STATE_TIMER,
    STATE_TEMPERATURE,
    STATE_FAN,
    STATE_SERIAL,
    STATE_RUN};
State currentState = STATE_MENU;                              //Estado inicial

//LED
const byte ledPin = A5;                                       //Pino do LED

void setup() {
  setupTimer1();                                              //Função de Setup do Timer 1
  setupButtons();                                             //Função de setup dos botões
  setupMenu();                                                //Função de setup do lcd
  setupTemperature();                                         //Função de setup do Relay
  pinMode(ledPin, OUTPUT);                                    //Declaração do pino do led como saida
  flagSelect = false;                                         //Corrigir problema com a flag estando ativa ao iniciar o código
}

void loop() {
  buttonsHandle();                                            //Função que checa flag dos botões e realiza funções especificas para cada menu

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
      if(countdownOver){
        buzzerHandle();                                       //Ativa o buzzer (buzzer.cpp)
        digitalWrite(ledPin, LOW);                            //Desliga o LED
        showEnd();                                            //Exibe texto no LCD (lcdMenu.cpp)        
      }
      else if(!flagRun){                                      //Caso flag run seja falsa
        digitalWrite(ledPin, LOW);                            //Desliga o LED
        TIMSK1 &= ~(1 << OCIE1A);                             //Reset bit OCIE1A do registrador TIMSK1, parando a contagem do Timer 1
        showRun();                                            //Exibe texto no LCD (lcdMenu.cpp)
      }
      else{                                                   //Caso a flag run seja verdadeira
        digitalWrite(ledPin, HIGH);                           //Liga o LED
        TIMSK1 |= (1 << OCIE1A);                              //Set bit OCIE1A do registrador TIMSK1, inicializando a contagem do Timer 1
        if(thermocoupleFlag){                                 //Caso a flag do sensor de temperatura seja verdadeira
          thermocoupleRead();                                 //Função para ler o sensor (temperature.cpp)
        }
        showRunning();                                        //Exibe texto no LCD (lcdMenu.cpp)
      }
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
      if(setMinutes < 50){
        setMinutes += 10;
      }
      else{
        setMinutes = 0;
        if(setHours < 24){
          setHours++;
        }
        else{setHours = 0;}
      }
    }
    if(currentState == STATE_TEMPERATURE){
      if(temperature < 250){
        temperature += 5;
      }
      else{temperature = 0;}
    }
    if (currentState == STATE_RUN) {
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
      setHours = 0;
      setMinutes = 0;
    }
    else if(currentState == STATE_TEMPERATURE){
      temperatureSet();
      currentState = STATE_MENU;
      temperature = 0;
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