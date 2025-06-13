#include "lcdMenu.h"
#include "timer.h"
#include "temperature.h"

//LCD
LiquidCrystal lcd(7, 8, 10, 11, 12, 13);

//Menu
uint8_t menuIndex = 0;
const char* menuItems[] = {
  "1 - Temporizador",
  "2 - Temperatura ",
  "3 - Ventilador  ",
  "4 - Serial      ",
  "5 - Iniciar     "};
const uint8_t menuQnt = sizeof(menuItems)/sizeof(menuItems[0]);

void setupMenu(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(1000);
  lcd.clear();
}

void showMenu(){
  lcd.setCursor(0, 0);
  lcd.print("Menu            ");
  lcd.setCursor(0, 1);
  lcd.print(menuItems[menuIndex]);
}

void showTimer(){
  char timeBuffer[9];

  lcd.setCursor(0, 0);
  lcd.print("Selecione o temp");

  lcd.setCursor(0, 1);
  sprintf(timeBuffer, "%02d:%02d:00", timerSetHours, timerSetMinutes);
  lcd.print(timeBuffer);
  lcd.print("         ");
}

void showTemp(){
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(temperatureSetPoint);
  lcd.write(byte(223));
  lcd.print("               ");
}

void showRun(){
  char timeBuffer[9];

  lcd.setCursor(0, 0);
  lcd.print("DESLIGADO       ");

  lcd.setCursor(0, 1);
  lcd.print(temperatureRead);
  lcd.write(byte(223));
  lcd.print(" ");

  sprintf(timeBuffer, "%02d:%02d:%02d", timerHours, timerMinutes, timerSeconds);
  lcd.print(timeBuffer);
  lcd.print("       ");
}

void showRunning(){
  char timeBuffer[9];

  lcd.setCursor(0, 0);
  lcd.print("LIGADO          ");

  lcd.setCursor(0, 1);
  lcd.print(temperatureRead);
  lcd.write(byte(223));
  lcd.print(" ");

  sprintf(timeBuffer, "%02d:%02d:%02d", timerHours, timerMinutes, timerSeconds);
  lcd.print(timeBuffer);
  lcd.print("                ");
}

void showEnd(){
  lcd.setCursor(0, 0);
  lcd.print("ALIMENTO PRONTO ");
  lcd.setCursor(0, 1);
  lcd.print("   APROVEITE!   ");
}

void showSerial(){
  lcd.setCursor(0, 0);
  lcd.print("Serial");
  static unsigned long lastSerial = 0;
  if(millis() - lastSerial >= 1000){ 
  Serial.print(temperatureRead);
  Serial.print("    ");
  Serial.print(timerHours);
  Serial.print(":");
  Serial.print(timerMinutes);
  Serial.print(":");
  Serial.print(timerSeconds);
  }
  lastSerial = millis();
}
