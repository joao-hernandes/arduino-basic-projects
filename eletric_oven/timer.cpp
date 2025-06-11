#include "timer.h"
#include "buzzer.h"
#include "buttons.h"
#include "temperature.h"
#include "control.h"

//Variaveis para o contador
volatile byte timerHours = 0;
volatile byte timerMinutes = 0;
volatile byte timerSeconds = 0;

volatile byte timerSetHours = 0;
volatile byte timerSetMinutes = 0;

volatile bool flagCountdownOver = false;
volatile bool flagCountdownActive = false;

//Variavel para controle de tempo da leitura do sensor de temperatura
volatile byte timerThermocouple = 0;

void setupTimer1(){
  noInterrupts();                                                   //Desabilita ocorrência de interrupções durante setup

  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 0;
  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);                                           //Habilita o modo de operação CTC (CLear timer on compare)
  TCCR1B |= (1 << CS12);                                            //Set o bit CS12 do registrador TCCR1B
  TCCR1B |= (1 << CS10);                                            //Set o bit CS10 do registrador TCCR1B selecionando pre scaler de 1024 para o timer 1 (Clock select bit)

  interrupts();                                                     //Habilita interrupções
}

void timerStop(){
  TIMSK1 &= ~(1 << OCIE1A);                                         //Desabilita Timer1 interrupt
}

void timerStart(){
  TIMSK1 |= (1 << OCIE1A);                                          //Habilita Timer1
}

void timerSetCountdown(){
  /*timerHours = timerSetHours;
  timerMinutes = timerSetMinutes;
  timerSeconds = 0;*/

  timerHours = 0;
  timerMinutes = timerSetHours;
  timerSeconds = timerSetMinutes;


  flagCountdownOver = false;
  flagCountdownActive = true;
  buzzerBips = 0;
}

ISR(TIMER1_COMPA_vect) {
  if(flagCountdownOver == true){                                    //Caso flag de contagem regressiva seja verdadeira
      buzzerBips++;                                                 //Incrementa váriavel para quantidade de bips do buzzer
      flagBipsBuzzer = !flagBipsBuzzer;                             //Inverte flag de acionamento do buzzer
    return;
  }

  if(flagCountdownActive){
    if(timerHours == 0 && timerMinutes == 0 && timerSeconds == 0){       
      flagCountdownOver = true;                                       //Habilita flag para fim da contagem
      flagCountdownActive = false;
      return;
    }
  }


  if(timerSeconds > 0){
      timerSeconds--;
  } 
  else{
    timerSeconds = 59;
    if(timerMinutes > 0){
        timerMinutes--;
    } 
    else {
      timerMinutes = 59;
      if (timerHours > 0) {
        timerHours--;
      } 
      else {                                                        //Timer1 chegou a 00:00:00
        timerHours = 0;
        timerMinutes = 0;
        timerSeconds = 0;
      }
    }
  }

  timerThermocouple++;
  if(flagRun && timerThermocouple >= 5){                            //Caso estaja no RUN e tenha contado 5 estouros do timer 1, faça
    timerThermocouple = 0;                                          //Zera a contagem de estouros
    thermocoupleFlag = true;                                        //Habilita a flag para medição do sensor de temperatura
  }

  flagControl = true;
}