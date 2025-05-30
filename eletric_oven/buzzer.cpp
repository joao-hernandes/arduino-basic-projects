#include "buzzer.h"
#include "timer.h"

volatile bool flagBuzzer = false;
volatile bool flagBips = false;
volatile byte buzzerBips = 0;

void setupBuzzer(){
  pinMode(buzzerPin, OUTPUT);                   //Declara o pino (perna maior) do buzzer como saida
}

void buzzerHandle(){
  if(buzzerBips <= 4 && countdownOver){
    buzzerPlay();
  }
  else{timerStop();noTone(buzzerPin);}         //Chama a função que para o Timer 1 e para o buzzer
}

void buzzerPlay(){
  if(flagBips){
    tone(buzzerPin, 500);                       //Ativa o buzzer com um frequência de 500Hz
  }
  else{noTone(buzzerPin);}                      //Para o buzzer
}