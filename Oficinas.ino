// Gira 90 graus nos 2 sentidos
#include  <Stepper.h> // inclue a biblioteca Stepper.h
 
const int PassoPorVolta = 500;  // Passo por Volta do Motor de Passo

int contador_card = 0;   // 0 -> 2
int contador_player = 0; // 0 -> 2

const int LED = A3;
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

int num_cards=1;
int num_players=1;

// Inicializa a biblioteca Stepper.h
// O motor de passo =>  MotorP
Stepper MotorP(PassoPorVolta, 8, 10, 9, 11);
 
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(botao_start, INPUT);
  pinMode(botao_card, INPUT);
  pinMode(botao_player, INPUT);

  for(int i=0; i<8;i++){
    pinMode(i, OUTPUT);
  }

  // pinMode(pino_a_card, OUTPUT);
  // pinMode(pino_b_card, OUTPUT);
  // pinMode(pino_c_card, OUTPUT);
  // pinMode(pino_d_card, OUTPUT);

  // pinMode(pino_a_player, OUTPUT);
  // pinMode(pino_b_player, OUTPUT);
  // pinMode(pino_c_player, OUTPUT);
  // pinMode(pino_d_player, OUTPUT);

  // Ajusta velocidade para 60 RPM
  MotorP.setSpeed(30);
}
 
void loop() {
  //Por padrão o jogo começa com 2 jogadores e 2 cartas
  int players = setNumPlayers();
  int cards = setNumCards();

  if(digitalRead(botao_start)){
    start(players, cards);
    delay(5000);
  }
}

void start(int players, int cards) {
  int passo = 2048/players;
  digitalWrite(LED, HIGH);

  for(int i=0; i<cards; i++) {
    for(int j=0; j<players; j++) {
      MotorP.step(passo);
      delay(1000);
    }
  }
  digitalWrite(LED, LOW);
}

int setNumPlayers(){  
  if(digitalRead(botao_player)){
    contador_player = (num_cards * (num_players+1)<= 52)? contador_player++: 0;
    delay(500);
  }
  num_players = (contador_player)%9 + 1;

  display(num_players, pino_a_player, pino_b_player, pino_c_player, pino_d_player);

  return num_players;
}

int setNumCards(){
  if(digitalRead(botao_card)){
    contador_card = ((num_cards+1) * num_players<= 52)? contador_card++ : 0;
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