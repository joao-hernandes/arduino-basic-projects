#include <LiquidCrystal.h>

//Botões
const int buttons[] = { 11, 12, 13};                             //Definição dos pinos de cada botão
const int numButtons = sizeof(buttons) / sizeof(buttons[0]);      //Definir quantidade de botões utilizados
bool stateButton[numButtons];                                     //Flag do estado de cada botão
//Debounce botões
bool lastState[] = {HIGH, HIGH, HIGH};                            //Iniciar o estado anterior de cada botão como alto
unsigned long lastDebounceTime[numButtons] = {0};
const unsigned long debounceDelay = 50;

//Menu
int menuIndex = 0;                                                //Index utilizado para definir qual item será exibido no lcd
const char* menuItems[] = {                                       //Itens do Menu  
  "1 - LED",
  "2 - Distancia",
  "3 - Motor"
  };
const int menuSize = sizeof(menuItems)/sizeof(menuItems[0]);       //Quantidade de itens no Menu
bool menuActive = false;                                           //Argumento para funcionalidades dentro de cada opção do menu

//LED
const int led = A0;                                                //LED conectado no pino A0
bool ledState = false;                                             //Estado inicial do LED

//LCD
LiquidCrystal lcd(2, 3, 6, 7, 8, 9);


void setup() {
  for (int i = 0; i < numButtons; i++){
      pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(led, OUTPUT);

//Configuração inicial do lcd
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(1000);
  displayMenu();
}

void loop() {
  readButtons();

//Caso esteja na primeira tela do menu
  if (!menuActive) {
    if(stateButton[0]){ buttonUp(); }
    if(stateButton[1]){ menuSelected(); }
    if(stateButton[2]){ buttonDown(); }
  }

//Caso esteja dentro de alguma função dentro do menu
  else {
    if(stateButton[0]){ buttonLeft(); }
    if(stateButton[1]){ menuSelected(); }
    if(stateButton[2]){ buttonRight(); }
  }

//Limpar a flag de cada botão
  for(int i = 0; i < numButtons; i++){
    stateButton[i] = 0;
  }
}

void readButtons() {
  for (int i = 0; i < numButtons; i++) {
    bool reading = digitalRead(buttons[i]);

    if (reading != lastState[i]) {
      lastDebounceTime[i] = millis();
    }

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      stateButton[i] = (reading == LOW);
    }
    lastState[i] = reading;
  }
}

void buttonUp(){
  menuIndex--;
  if(menuIndex < 0){
    menuIndex = menuSize - 1;
  }
  displayMenu();
}

void buttonDown(){
  menuIndex++;
  if(menuIndex >= menuSize){
    menuIndex = 0;
  }
  displayMenu();
}

void buttonLeft(){
  if(menuIndex == 0){
    ledState = false;
    digitalWrite (led, LOW);
  }
  if(menuIndex == 1){

  }
  if(menuIndex == 2){

  }
}

void buttonRight(){
  if(menuIndex == 0){
    ledState = true;
    digitalWrite (led, HIGH);
  }
  if(menuIndex == 1){

  }
  if(menuIndex == 2){

  }
}

void menuSelected() {
  if (!menuActive) {
    menuActive = true;
    if(menuIndex == 0){
      displayLED();
    }
    else if(menuIndex == 1){
      displayDistance();
    }
    else if(menuIndex == 2){
      displayMotor();
    }
  } else {
    // If already in submenu, pressing SELECT returns to main menu
    menuActive = false;
    displayMenu();
  }
}

void displayMenu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu");
  lcd.setCursor(0, 1);
  lcd.print(menuItems[menuIndex]);
}

void displayLED(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LED Selection");
  lcd.setCursor(0, 1);
  lcd.print("OFF/ON");
}

void displayDistance() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distancia Mode");
}

void displayMotor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor Mode");
}