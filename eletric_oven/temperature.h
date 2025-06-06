#ifndef TEMPERATURE_h
#define TEMPERATURE_H

#include <Arduino.h>

const byte thermocouplePin = A2;                    //Pino do sensor de temperatura
const byte relayPin = A0;                           //Pino do relay

//Variaveis para seleção de temperatura
volatile extern byte temperature;
volatile extern byte temperatureSetPoint;

//Variaveis para o sensor
extern float temperatureAdcRead;
extern float temperatureVoltage;
extern float temperatureResistance;
extern float temperatureKelvin;
extern float temperatureRead;
volatile extern bool thermocoupleFlag;

volatile extern byte temperatureError;

void setupTemperature();
void temperatureSet();
void temperatureCycle();

//Funções para o sensor
void setupThermocouple();
void thermocoupleRead();

#endif
