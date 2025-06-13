#include "control.h"
#include "temperature.h"
#include "timer.h"
#include "buzzer.h"
#include "lcdMenu.h"
#include "buttons.h"
#include "eletric_oven.h"

bool firstStopRun = true;
bool firstRun = true;

volatile bool flagControl = false;
uint8_t controlCounter = 0;
uint8_t controlRelayTime = 0;

const uint8_t ledPin = A5;
const uint8_t relayPin = A0;

void setupControl(){
  pinMode(relayPin, OUTPUT);                                  //Declaração do pino do rele como saida
  pinMode(ledPin, OUTPUT);                                    //Declaração do pino do led como saida
  digitalWrite(relayPin, HIGH);

}

void controlRelay(){
  if(!flagControl){
    return;
  }

  flagControl = false;
  controlCounter++;

  if(controlCounter >= 5){
    controlCounter = 0;
  
  } else if (controlCounter == 1){
    controlRelayTime = (temperatureError > 40) ? 5 :
                      (temperatureError > 20) ? 3 :
                      (temperatureError > 10) ? 2 :
                      (temperatureError > 1)  ? 1 : 0;
  }

  if(controlCounter <= controlRelayTime){
    digitalWrite(relayPin, LOW);
    return;
  }

  digitalWrite(relayPin, HIGH);
}

void controlHandle(){
  if(!flagRun){                                           //Caso flag run seja falsa
    if(firstStopRun){
      firstStopRun = false;
      peripheralsStop();                                  //Para o funcionamento de todos os perifericos
    }
    firstRun = true;                                      //Reseta flag de primeira ativação do Run
  }

  else{                                                   //Caso a flag run seja verdadeira
    if(firstRun){
      firstRun = false;
      digitalWrite(ledPin, HIGH);                         //Liga o LED
      TIMSK1 |= (1 << OCIE1A);                            //Set bit OCIE1A do registrador TIMSK1, inicializando a contagem do Timer 1
    }
    if(thermocoupleFlag){                                 //Caso a flag do sensor de temperatura seja verdadeira
      thermocoupleFlag = false;                           //Limpa a flag
      thermocoupleRead();                                 //Função para ler o sensor (temperature.cpp)
      temperatureGetError();                              //Função para gerar o erro entre temperaturas
    }
    controlRelay();                                       //Define o tempo em que o relay ficara ligado
    firstStopRun = true;                                  //Reseta flag de primeira ativação do parada do run
  }
}

void peripheralsStop(){
  TIMSK1 &= ~(1 << OCIE1A);                                   //Reset bit OCIE1A do registrador TIMSK1, parando a contagem do Timer 1
  digitalWrite(ledPin, LOW);                                  //Desliga o LED
  digitalWrite(relayPin, HIGH);                               //Desliga o relé
  noTone(buzzerPin);                                          //Desliga o buzzer
}

void controlStop(){
  showEnd();                                                  //Exibe texto no LCD (lcdMenu.cpp)
  digitalWrite(ledPin, LOW);                                  //Desliga o LED  
  if(buzzerBips <= 4 && flagCountdownOver){
    buzzerPlay();
  }

  else{
    peripheralsStop();
    currentState = STATE_MENU;                            //Volta para o menu principal
    flagRun = false;
    flagCountdownOver = false;
  }
}