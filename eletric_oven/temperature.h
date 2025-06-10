#ifndef TEMPERATURE_h
#define TEMPERATURE_H

#include <Arduino.h>

const byte thermocouplePin = A2;                    //Pino do sensor de temperatura

//Variaveis para seleção de temperatura
volatile extern float temperature;
volatile extern float temperatureSetPoint;

//Variaveis para o sensor
extern float temperatureAdcRead;
extern float temperatureVoltage;
extern float temperatureResistance;
extern float temperatureKelvin;
extern float temperatureRead;
volatile extern bool thermocoupleFlag;

volatile extern float temperatureError;

void setupTemperature();
void temperatureSet();

//Funções para o sensor
void setupThermocouple();
void thermocoupleRead();
void temperatureGetError();

#endif
