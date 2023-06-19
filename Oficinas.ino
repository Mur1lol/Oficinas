#include  <Stepper.h> 
#include <Servo.h>
 
const int PassoPorVolta = 500;  // Passo por Volta do Motor de Passo

//Iniciando as variaveis
int contador_card = 0;   // 0 -> 1
int contador_player = 0; // 0 -> 1
int num_cards=1;
int num_players=1;

//Definindo os pinos
const int botao_start = A2;
const int botao_card = A1;
const int botao_player = A0;

const int pino_a_card = 3; 
const int pino_b_card = 0;
const int pino_c_card = 1;
const int pino_d_card = 2;

const int pino_a_player = 7; 
const int pino_b_player = 4; 
const int pino_c_player = 5; 
const int pino_d_player = 6;

const int servo = 12;
const int rele = 13;

Stepper MotorP(PassoPorVolta, 8, 10, 9, 11);

Servo myservo; 
 
void setup() {
  pinMode(botao_start, INPUT);
  pinMode(botao_card, INPUT);
  pinMode(botao_player, INPUT);

  pinMode(rele, OUTPUT);

  for(int i=0; i<8;i++){
    pinMode(i, OUTPUT);
  }

  myservo.attach(servo);

  // Ajusta velocidade para 49 RPM
  MotorP.setSpeed(49);

  digitalWrite(rele, HIGH);
}
 
void loop() {
  //Por padrão o jogo começa com 1 jogador e 1 carta
  int players = setNumPlayers();
  int cards = setNumCards();

  if(digitalRead(botao_start)){
    start(players, cards);
    delay(1000);
  }
}

void start(int players, int cards) {
  int passo = 2048/players;
  
  for(int i=0; i<cards; i++) {
    for(int j=0; j<players; j++) {
      MotorP.step(passo);
      delay(500);
      digitalWrite(rele, LOW);
      myservo.write(180); // Comando para mandar o servo para posição 180
      delay(500); // Espera de 500 ms
      myservo.write(0); // Comando para mandar o servo para posição 0
      delay(1000); // Espera de 500 ms
      digitalWrite(rele, HIGH);
    }
  }
}

int setNumPlayers(){  
  if(digitalRead(botao_player)){
    contador_player = (num_cards * (num_players+1)<= 52)? contador_player+1: 0;
    delay(500);
  }
  num_players = (contador_player)%9 + 1;

  display(num_players, pino_a_player, pino_b_player, pino_c_player, pino_d_player);

  return num_players;
}

int setNumCards(){
  if(digitalRead(botao_card)){
    contador_card = ((num_cards+1) * num_players<= 52)? contador_card+1 : 0;
    delay(500);
  }
  num_cards = (contador_card)%9 + 1;

  display(num_cards, pino_a_card, pino_b_card, pino_c_card, pino_d_card);

  return num_cards;
}

void display(int value, int A, int B, int C, int D) {
  if(value == 1) {
    // aciona os bits de modo a formar o número 0001 = 1 (um):
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
  }
  else if(value == 2) {
    // aciona os bits de modo a formar o número 0010 = 2 (dois):
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
  }
  else if(value == 3) {
    // aciona os bits de modo a formar o número 0011 = 3 (três):
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
  }
  else if(value == 4) {
    // aciona os bits de modo a formar o número 0100 = 4 (quatro):
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
  }
  else if(value == 5) {
    // aciona os bits de modo a formar o número 0101 = 5 (cinco):
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
  }
  else if(value == 6) {
    // aciona os bits de modo a formar o número 0110 = 6 (seis):
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
  }
  else if(value == 7) {
    // aciona os bits de modo a formar o número 0111 = 7 (sete):
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
  }
  else if(value == 8) {
    // aciona os bits de modo a formar o número 1000 = 8 (oito):
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
  }
  else if(value == 9) {
    // aciona os bits de modo a formar o número 1001 = 9 (nove):
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
  }
}
