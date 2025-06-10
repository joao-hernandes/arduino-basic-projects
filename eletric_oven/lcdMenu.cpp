#include "lcdMenu.h"
#include "timer.h"
#include "temperature.h"

//LCD
LiquidCrystal lcd(7, 8, 10, 11, 12, 13);

//Menu
byte menuIndex = 0;
const char* menuItems[] = {
  "1 - Temporizador",
  "2 - Temperatura ",
  "3 - Ventilador  ",
  "4 - Serial      ",
  "5 - Iniciar     "};
const byte menuQnt = sizeof(menuItems)/sizeof(menuItems[0]);

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
  lcd.setCursor(0, 0);
  lcd.print("Selecione o temp");
  lcd.setCursor(0, 1);

  byte h = timerSetHours;
  byte m = timerSetMinutes;

  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":00           ");
}

void showTemp(){
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print("               ");
}

void showRun(){
  lcd.setCursor(0, 0);
  lcd.print("DESLIGADO       ");
  lcd.setCursor(0, 1);
  lcd.print(temperatureRead);
  lcd.print(" ");
  lcd.print(timerHours);
  lcd.print(":");
  lcd.print(timerMinutes);
  lcd.print(":");
  lcd.print(timerSeconds);
}

void showRunning(){
  lcd.setCursor(0, 0);
  lcd.print("LIGADO          ");
  lcd.setCursor(0, 1);
  lcd.print(temperatureRead);
  lcd.print(" ");
  lcd.print(timerHours);
  lcd.print(":");
  lcd.print(timerMinutes);
  lcd.print(":");
  lcd.print(timerSeconds);
  lcd.print("                ");
}

void showEnd(){
  lcd.setCursor(0, 0);
  lcd.print("ALIMENTO PRONTO");
  lcd.setCursor(0, 1);
  lcd.print("   APROVEITE!   ");
}

void showSerial(){

}
