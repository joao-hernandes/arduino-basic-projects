#ifndef LCDMENU_H
#define LCDMENU_H

#include <Arduino.h>
#include <LiquidCrystal.h>

extern byte menuIndex;
extern const char* menuItems[];
extern const byte menuQnt;

void setupMenu();
void showMenu();
void showTimer();
void showTemp();
void showSerial();
void showRun();
void showEnd();
void showRunning();

#endif