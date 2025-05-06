#include <Servo.h>
Servo myservo;

//HC-SR04
const int trigPin = 12;
const int echoPin = 13;
int distance;
int rawDistance;
long duration;

//LED
const int ledPin[] = {5, 6, 7};
const int numLed = sizeof(ledPin)/sizeof(ledPin[0]);

//SERVO
bool isMoving = false;
const int moveTime = 300;
unsigned long movingTime;
int currentPos = 0;
int waveDirection = 1; // 1 for increasing, -1 for decreasing

void setup() {
//Definir pinos led como saida
  for(int i = 0; i < numLed; i++){
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }

//Definir pinos sensor de distância ultrassonico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

//Definir pino do servo motor e ângulo inicial
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  measurement();

  if(distance <= 30){
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[2], LOW);
    myservo.write(0);
  }
  if(distance > 30 && distance < 60){
    digitalWrite(ledPin[0], LOW);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], LOW);
    wave();
  }
  if(distance >= 60){
    digitalWrite(ledPin[0], LOW);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[2], HIGH);
    myservo.write(180);
  }
}

void wave(){
  if(!isMoving){
    isMoving = true;
    movingTime = millis();
    
//Atualiza posição
    currentPos += 45 * waveDirection;
    
//Reverte direção nos extremos
    if (currentPos >= 180 || currentPos <= 0) {
      waveDirection *= -1;
    }  
    myservo.write(currentPos);
  }
  
//Checa se passou tempo o suficiente para o proximo movimento
  if(millis() - movingTime > moveTime){
    isMoving = false;
  }
}

void measurement(){
  float sum = 0;
  for(int i = 0; i < 5; i++){
    digitalWrite(trigPin, LOW);
    delay(10);
    digitalWrite(trigPin, HIGH);
    delay(2);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);                //Espera o pino do ECHO mudar para alto, e armazena o tempo(ms) que leva para voltar ao estado anterior
    sum += (duration * 0.0343)/2;                     //Tempo que o pino ECHO ficou alto, multiplicado pela velocidade do som em segundos dividido por 2 pois é o tempo de inda e volta da onda
    delay(10);
  }
  distance = sum/5;
}