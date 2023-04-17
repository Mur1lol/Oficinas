// Gira 90 graus nos 2 sentidos
#include  <Stepper.h> // inclue a biblioteca Stepper.h
 
const int PassoPorVolta = 500;  // Passo por Volta do Motor de Passo

bool botao_ativo = false;

int contador_card = 0;   // 0 -> 2
int contador_player = 0; // 0 -> 2

const int LED = A0;
const int botao_start = A1;
const int botao_card = A2;
const int botao_player = A3;

const int pino_a = 11; 
const int pino_b = 8; 
const int pino_c = 9; 
const int pino_d = 10;
 
// Inicializa a biblioteca Stepper.h
// O motor de passo =>  MotorP
Stepper MotorP(PassoPorVolta, 4, 6, 5, 7);
 
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(botao_start, INPUT);
  pinMode(botao_card, INPUT);
  pinMode(botao_player, INPUT);

  pinMode(pino_a, OUTPUT);
  pinMode(pino_b, OUTPUT);
  pinMode(pino_c, OUTPUT);
  pinMode(pino_d, OUTPUT);

  // Ajusta velocidade para 60 RPM
  MotorP.setSpeed(60);
}
 
void loop() {
  //Por padrão o jogo começa com 2 jogadores e 2 cartas
  int players = setNumPlayers();
  int cards = setNumCards();

  if(digitalRead(botao_start)){
    start(players, cards);
    delay(5000);
  }

  if(botao_ativo){
    
  }

}

void start(int players, int cards) {
  /*
  angulo/0,175781

  2 pessoas - 180º  - 1024
  3 pessoas - 120º  - 683
  4 pessoas - 90º   - 512
  5 pessoas - 72º   - 410
  6 pessoas - 60º   - 341
  7 pessoas - 51,4º - 292
  8 pessoas - 45º   - 256
  9 pessoas - 40º   - 228
  */

  int passo[8] = {1024,683,512,410,341,292,256,228};
  digitalWrite(LED, HIGH);

  for(int x=0; x<8; x++){
    passo[x] = passo[x]/2;
  }

  for(int i=0; i<cards; i++) {
    for(int j=0; j<players; j++) {
      MotorP.step(passo[players-2]);
      delay(1000);
    }

    for(int j=0; j<players; j++) {
      MotorP.step(passo[players-2]*-1);
      delay(1000);
    }
    
  }

  botao_ativo = false;
  digitalWrite(LED, LOW);
}

int setNumPlayers(){
  int num_players;
  
  if(digitalRead(botao_player)){
    contador_player++;
    delay(500);
  }
  num_players = (contador_player)%8 + 2;

  //display(num_players);

  return num_players;
}

int setNumCards(){
  int num_cards;
 
  if(digitalRead(botao_card)){
    contador_card++;
    delay(500);
  }
  num_cards = (contador_card)%8 + 2;

  display(num_cards);

  return num_cards;
}

void display(int value) {
  if(value == 2) {
    // aciona os bits de modo a formar o número 0010 = 2 (dois):
  digitalWrite(pino_a, LOW);
  digitalWrite(pino_b, HIGH);
  digitalWrite(pino_c, LOW);
  digitalWrite(pino_d, LOW);
  }
  else if(value == 3) {
    // aciona os bits de modo a formar o número 0011 = 3 (três):
  digitalWrite(pino_a, HIGH);
  digitalWrite(pino_b, HIGH);
  digitalWrite(pino_c, LOW);
  digitalWrite(pino_d, LOW);
  }
  else if(value == 4) {
    // aciona os bits de modo a formar o número 0100 = 4 (quatro):
  digitalWrite(pino_a, LOW);
  digitalWrite(pino_b, LOW);
  digitalWrite(pino_c, HIGH);
  digitalWrite(pino_d, LOW);
  }
  else if(value == 5) {
    // aciona os bits de modo a formar o número 0101 = 5 (cinco):
  digitalWrite(pino_a, HIGH);
  digitalWrite(pino_b, LOW);
  digitalWrite(pino_c, HIGH);
  digitalWrite(pino_d, LOW);
  }
  else if(value == 6) {
    // aciona os bits de modo a formar o número 0110 = 6 (seis):
  digitalWrite(pino_a, LOW);
  digitalWrite(pino_b, HIGH);
  digitalWrite(pino_c, HIGH);
  digitalWrite(pino_d, LOW);
  }
  else if(value == 7) {
    // aciona os bits de modo a formar o número 0111 = 7 (sete):
  digitalWrite(pino_a, HIGH);
  digitalWrite(pino_b, HIGH);
  digitalWrite(pino_c, HIGH);
  digitalWrite(pino_d, LOW);
  }
  else if(value == 8) {
    // aciona os bits de modo a formar o número 1000 = 8 (oito):
  digitalWrite(pino_a, LOW);
  digitalWrite(pino_b, LOW);
  digitalWrite(pino_c, LOW);
  digitalWrite(pino_d, HIGH);
  }
  else if(value == 9) {
    // aciona os bits de modo a formar o número 1001 = 9 (nove):
  digitalWrite(pino_a, HIGH);
  digitalWrite(pino_b, LOW);
  digitalWrite(pino_c, LOW);
  digitalWrite(pino_d, HIGH);
  }
}