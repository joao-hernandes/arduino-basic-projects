#include <LiquidCrystal.h>
#include <Servo.h>

Servo myServo;

//Botões
const int buttons[] = { 11, 12, 13};                              //Definição dos pinos de cada botão
const int numButtons = sizeof(buttons) / sizeof(buttons[0]);      //Definir quantidade de botões utilizados
bool stateButton[numButtons];                                     //Flag do estado de cada botão
//Debounce botões
bool lastState[] = {HIGH, HIGH, HIGH};                            //Iniciar o estado anterior de cada botão como alto
unsigned long lastDebounceTime[numButtons] = {0};
const unsigned long debounceDelay = 90;

//Menu
int menuIndex = 0;                                                //Index utilizado para definir qual item será exibido no lcd
const char* menuItems[] = {                                       //Itens do Menu  
  "1 - LED",
  "2 - Distancia",
  "3 - Motor"
  };
const int menuSize = sizeof(menuItems)/sizeof(menuItems[0]);      //Quantidade de itens no Menu
bool menuActive = false;                                          //Argumento para funcionalidades dentro de cada opção do menu

//LED
const int led = A0;                                               //LED conectado no pino A0
bool ledState = false;                                            //Estado inicial do LED

//LCD
LiquidCrystal lcd(2, 3, 6, 7, 8, 9);

//Sensor de distância
const int trigPin = A3;
const int echoPin = A2;
long duration;
int distance;
bool inDistance = false;
bool isFirstTime = false;                                         //Primeira vez que exibi no menu
unsigned long lastShow = 0;                                       //Variavel para armazenar tempo entre cada exibição do sensor de distancia
const unsigned long showDelay = 1000;                             //Espaço para amostragem do sensor

//--------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  for (int i = 0; i < numButtons; i++){
      pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(led, OUTPUT);

//Configura Sensor
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

//Configuração inicial do lcd
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  displayMenu();

//Configuração Servo Motor
  myServo.attach(A5);                                             //Pino conectado
  myServo.write(0);                                               //Posição Inicial
}

//--------------------------------------------------------------------------------------------------------------------------------------
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

  if(inDistance == true){
    if(isFirstTime){
      lcd.clear();
      isFirstTime = false;
    }

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    lcd.setCursor(0, 0);
    lcd.print("Distancia Mode");

    if(millis() - lastShow > showDelay){
      lcd.setCursor(0, 1);
      lcd.print(distance);
      lcd.print(" cm ");

      lastShow = millis();
    }
  }

//Limpar a flag de cada botão
  for(int i = 0; i < numButtons; i++){
    stateButton[i] = 0;
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------------------------------------------
void buttonUp(){
  menuIndex--;
  if(menuIndex < 0){
    menuIndex = menuSize - 1;
  }
  displayMenu();
}

//--------------------------------------------------------------------------------------------------------------------------------------
void buttonDown(){
  menuIndex++;
  if(menuIndex >= menuSize){
    menuIndex = 0;
  }
  displayMenu();
}

//--------------------------------------------------------------------------------------------------------------------------------------
void buttonLeft(){
  if(menuIndex == 0){
    ledState = false;
    digitalWrite (led, LOW);
  }
  if(menuIndex == 1){
    return;
  }
  if(menuIndex == 2){
    myServo.write(0);
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------
void buttonRight(){
  if(menuIndex == 0){
    ledState = true;
    digitalWrite (led, HIGH);
  }
  if(menuIndex == 1){
    return;
  }
  if(menuIndex == 2){
    myServo.write(180);
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------
void menuSelected() {
  if (!menuActive) {
    menuActive = true;
    if(menuIndex == 0){
      displayLED();
    }
    else if(menuIndex == 1){
      inDistance = true;
      isFirstTime = true;
    }
    else if(menuIndex == 2){
      displayMotor();
    }
  } else {
    // If already in submenu, pressing SELECT returns to main menu
    menuActive = false;
    inDistance = false;
    displayMenu();
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------
void displayMenu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu");
  lcd.setCursor(0, 1);
  lcd.print(menuItems[menuIndex]);
}

//--------------------------------------------------------------------------------------------------------------------------------------
void displayLED(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LED Selection");
  lcd.setCursor(0, 1);
  lcd.print("OFF/ON");
}

//--------------------------------------------------------------------------------------------------------------------------------------
void displayDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Modo Distancia");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print("cm");
}

//--------------------------------------------------------------------------------------------------------------------------------------
void displayMotor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Modo Motor");
  lcd.setCursor(0, 1);
  lcd.print("0/180");
}