#include "temperature.h"

volatile float temperature = 0;
volatile float temperatureSetPoint = 0;
volatile float temperatureError = 0;

//Variaveis para leitura da temperatura
float temperatureAdcRead = 0;
float temperatureVoltage = 0;
float temperatureResistance = 0;
float temperatureKelvin = 0;
float temperatureRead = 0;

volatile bool thermocoupleFlag = false;

void setupTemperature(){
  pinMode(thermocouplePin, INPUT);
}
//Define a temperatura obejtivo
void temperatureSet(){
  temperatureSetPoint = temperature;
}
//Lê a temperatura real
void thermocoupleRead(){
  temperatureAdcRead = 0;

  for(byte i = 0; i < 5; i++){                                                                          //Mede a temperatura 5 vezes
    temperatureAdcRead += analogRead(thermocouplePin);                                                  //Soma as 5 leituras na mesma variavel
  }
  float media = temperatureAdcRead/5;                                                                   //Temperatura lida é a média das 5 leituras
  temperatureVoltage = media * (5.0/1023.0);                                                            //Converte ADC para tensão
  temperatureResistance = 10000.0 * (5.0/temperatureVoltage - 1.0);                                     //Calcula a resistência do thermistor
  temperatureKelvin = 1.0 / ( (1.0 / 298.15) + (1.0 / 3950) * log(temperatureResistance / 10000.0) );   //Equação do parâmetro Beta
  temperatureRead = temperatureKelvin - 273.15;                                                         //Converte de Kelvin para Celsius
}

void temperatureGetError(){
  temperatureError = temperatureSetPoint - temperatureRead;                                             //Compara a temperatura definida pelo usuário e a lida, gerando o erro entre elas
  Serial.println(temperatureError);
}