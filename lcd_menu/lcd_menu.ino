
//Botões
const int buttons[] = { 10, 11, 12 };
const int numButtons = sizeof(buttons) / sizeof(buttons[0]);
bool stateButton[numButtons];
bool reading;
bool lastState[] = {HIGH, HIGH, HIGH};
unsigned long lastDebounceTime[numButtons] = {0};
const unsigned long debounceDelay = 50;

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  readButtons();
}

void readButtons() {
  for (int i = 0; i < numButtons; i++) {
    reading = digitalRead(buttons[i]);

    if (reading != lastState[i]) {
      lastDebounceTime[i] = millis();
    }

    if(millis() - lastDebounceTime[i] >= debounceDelay){
      stateButton[i] = reading; 
    }

    lastState[i] = reading;
  }
}
