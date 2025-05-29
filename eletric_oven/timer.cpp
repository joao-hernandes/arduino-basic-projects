#include "timer.h"
#include "buzzer.h"

volatile byte hours = 0;
volatile byte minutes = 0;
volatile byte seconds = 0;

volatile byte setHours = 0;
volatile byte setMinutes = 0;

volatile bool countdownOver = false;

void setupTimer1(){
  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 0;
  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  TCCR1B |= (1 << CS10);

  interrupts();
}

void timerStop(){
  TIMSK1 &= ~(1 << OCIE1A); //Desabilia Timer1 interrupt
  
}

void timerStart(){
  TIMSK1 |= (1 << OCIE1A);  //Habilita Timer1
}

void timerSetCountdown(){
  /*hours = setHours;
  minutes = setMinutes;
  seconds = 0;*/

  hours = 0;
  minutes = setHours;
  seconds = setMinutes;


  countdownOver = false;
  buzzerBips = 0;
}

ISR(TIMER1_COMPA_vect) {
  if(countdownOver == true){
      buzzerBips++;
      flagBips = !flagBips;
    return;
  }

  if(hours == 0 && minutes == 0 && seconds == 0){
    countdownOver = true;
    return;
  }

  if(seconds > 0){
      seconds--;
  } 
  else{
    seconds = 59;
    if(minutes > 0){
        minutes--;
    } 
    else {
      minutes = 59;
      if (hours > 0) {
        hours--;
      } 
      else {
        // Timer reached 00:00:00
        hours = 0;
        minutes = 0;
        seconds = 0;
      }
    }
  }
}