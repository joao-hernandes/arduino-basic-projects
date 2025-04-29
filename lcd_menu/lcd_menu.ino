//Botões
const int buttons[] = { 10, 11, 12 };                             //Definição dos pinos de cada botão
const int numButtons = sizeof(buttons) / sizeof(buttons[0]);      //Definir qunatidade de botões utilizados
bool stateButton[numButtons];                                     //Flag do estado de cada botão
//Debounce botões
bool reading;
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


void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(led, OUTPUT);
}

void loop() {
  readButtons();

//Caso esteja na primeira tela do menu
  if(menuActive == LOW){
    if(stateButton[0]){buttonUp();}
    if(stateButton[1]){menuSelected();}
    if(stateButton[2]){buttonDown();}
  }
//Caso esteja dentro de alguma função dentro do menu
  if(menuActive == HIGH){
    if(stateButton[0]){buttonLeft();}
    if(stateButton[1]){menuSelected();}
    if(stateButton[2]){buttonRight();}
  }
//Limpar a flag de cada botão
  for(int i = 0; i < numButtons; i++){
    stateButton[i] = 0;
  }

}

void readButtons() {
  for (int i = 0; i < numButtons; i++) {
    reading = digitalRead(buttons[i]);

    if (reading != lastState[i]) {
      lastDebounceTime[i] = millis();
    }

    if (millis() - lastDebounceTime[i] >= debounceDelay) {
      if (reading == LOW && lastState[i] == HIGH) {                //Garante que só muda o estado do botão quando ele for solto
        stateButton[i] = 1;
      }
    }

    lastState[i] = reading;
  }
}

void buttonUp(){
  menuIndex--;
  if(menuIndex < 0){
    menuIndex = menuSize - 1;
  }

}

void buttonDown(){
  menuIndex++;
  if(menuIndex >= menuSize){
    menuIndex = 0;
  }
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

void menuSelected(){
  menuActive = !menuActive;
}
