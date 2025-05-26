#include "lcdMenu.h"

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

void showTemp(){
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:     ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void showRun(){
  lcd.setCursor(0, 0);
  lcd.print("LIGADO          ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
