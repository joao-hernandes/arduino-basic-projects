#include "temperature.h"

volatile byte temperature = 0;
volatile byte temperatureSetPoint = 0;
volatile byte temperatureError = 0;

//Variaveis para leitura da temperatura
float temperatureAdcRead = 0;
float temperatureVoltage = 0;
float temperatureResistance = 0;
float temperatureKelvin = 0;
float temperatureRead = 0;

volatile bool thermocoupleFlag = false;

void setupTemperature(){
  pinMode(relayPin, OUTPUT);
  pinMode(thermocouplePin, INPUT);
}
//Define a temperatura obejtivo
void temperatureSet(){
  temperatureSetPoint = temperature;
}
//Lê a temperatura real
void thermocoupleRead(){
  for(byte i = 0; i < 5; i++){                                                                          //Afere a temperatura 5 vezes
    temperatureAdcRead += analogRead(thermocouplePin);                                                  //Soma as 5 leituras na mesma variavel
  }
  float media = temperatureAdcRead/5;                                                                   //Temperatura lida é a média das 5 leituras
  temperatureVoltage = media * (5.0/1023.0);                                                            //5V tensão de alimentação do arduino, dividido por 1023 que é a resolução de leitura do pino analógico, multiplicado pelo valor lido no pino A0
  temperatureResistance = 10000.0 * (5.0/temperatureVoltage - 1.0);                                     //
  temperatureKelvin = 1.0 / ( (1.0 / 298.15) + (1.0 / 3950) * log(temperatureResistance / 10000.0) );
  temperatureRead = temperatureKelvin - 273.15;
}
//Gera o erro entre as temperaturas
void temperatureCycle(){
  temperatureError = temperatureSetPoint - temperatureRead;                                             //Compara a temperatura definida pelo usuário e a lida, gerando o erro entre elas
}