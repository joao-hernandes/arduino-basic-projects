#include "control.h"
#include "temperature.h"

volatile bool flagControl = false;
byte controlCounter = 0;
byte controlRelayTime = 0;

void setupControl(){
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void controlRelay(){
  if(flagControl){

    flagControl = false;
    controlCounter++;

    if(controlCounter == 1){
      controlRelayTime = (temperatureError > 40) ? 5 :
                         (temperatureError > 20) ? 3 :
                         (temperatureError > 10) ? 2 :
                         (temperatureError > 1)  ? 1 : 0;
    }

    if(controlCounter <= controlRelayTime){
      digitalWrite(relayPin, LOW);
    }   
    else{digitalWrite(relayPin, HIGH);}

    if(controlCounter >= 5){
      controlCounter = 0;
    }
  }
}