/*
LENGUAGES: PT-BR

OBJETIVO
  Fazer um jogo semelhante aos jogos de plataforma, onde o jogador irá controlar um personagem
  e deverá desviar dos obstáculos do cenário
 

PASSO A PASSO
  - Design dos objetos do cenário (criar a imagem do boneco, do balão e do fogo)
  - Gerar o cenário
  - Movimentação do cenário
  - Movimentação do personagem
  - Sistema de pontuação
  - Sistema de colisão
  - Sistema de reinício do jogo

  */

// Biblioteca do LCD 16x2
#include <LiquidCrystal.h>

// pinos do LCD 16x2
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

//Funções
void pontuacao(void);
void colisao(void);
void iniciar(void);


// Oo 8 arrays que irão formar o design do cenário
byte boneco_def[8] = 
{
  B00100,
  B01010,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};

byte fogo_def[8] = 
{
  B00000,
  B00000,
  B00000,
  B00100,
  B01010,
  B10101,
  B01110,
  B11111
};

byte balao_def[8] = 
{
  B01110,
  B10001,
  B10001,
  B01110,
  B01010,
  B01010,
  B11111,
  B00000
};

//Variáveis

int botao1 = 13;
int posicao_balao = 9;
int posicao_balao2 = 10;
int posicao_balao3 = 6;
int posicao_fogo = 12;
int posicao_fogo2 = 11;
int posicao_fogo3 = 7;
int posicao_boneco = 1;
int contador = 0;
int pontos = 0;
int random1;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;


void setup()
{
  // associando os objetos crriados à numeros
  lcd.createChar(1,boneco_def);
  lcd.createChar(2,fogo_def);
  lcd.createChar(3, balao_def);

  //botao
  pinMode(botao1, INPUT_PULLUP);

  // inicialização do LCD
  lcd.begin(0, 2);

  //preparação da função random
  randomSeed(analogRead(0));
}
void loop(){

   
  //LÓGICA DA MOVIMENTAÇÃO DO CENÁRIO E DO PERSONAGEM
  iniciar();

  //Movimentação do boneco
  if(digitalRead(botao1) == LOW) posicao_boneco = 0;
  else{posicao_boneco = 1;}

  //Movimentação do cenário
  lcd.clear();
  pontuacao();
  lcd.setCursor(0,posicao_boneco);
  lcd.write(1);
  if(posicao_fogo >= 0){
  lcd.setCursor(posicao_fogo,1);
  lcd.write(2);
  }
  if(posicao_fogo2 >= 0){
  lcd.setCursor(posicao_fogo2,1);
  lcd.write(2);
  }
  if(posicao_fogo3 >= 0){
  lcd.setCursor(posicao_fogo3,1);
  lcd.write(2);
  }
  if(posicao_balao >= 0){
  lcd.setCursor(posicao_balao,0);
  lcd.write(3);
  }
  if(posicao_balao2 >= 0){
  lcd.setCursor(posicao_balao2,0);
  lcd.write(3);
  }
  if(posicao_balao3 >= 0){
  lcd.setCursor(posicao_balao3,0);
  lcd.write(3);
  }
  delay(500); // velocidade do jogo

  //sistema de colisão
  colisao();

  // Comtinuação da movimentação do cenário - reposicionamento do cenario quando eles chegam ao fim

  posicao_balao--;
  if(posicao_balao < 0){
    
    lcd.clear();
    if(random(5) == 0) posicao_balao = 12; flag1 = 1;

  }
  posicao_balao2--;
  if(posicao_balao2 < 0){
    
    lcd.clear();
    if(random(5) == 0) posicao_balao2 = 12; flag1 = 1;

  }
  posicao_balao3--;
  if(posicao_balao3 < 0){
    
    lcd.clear();
    if(random(5) == 0) posicao_balao3 = 12; flag1 = 1;

  }
  posicao_fogo--;
  if(posicao_fogo < 0){
    lcd.clear();
    if(random(5) == 0 && flag1 == 0) posicao_fogo = 12;
  }
  posicao_fogo2--;
  if(posicao_fogo2 < 0){
    lcd.clear();
    if(random(5) == 0 && flag1 == 0) posicao_fogo2 = 12;
  }
  posicao_fogo3--;
  if(posicao_fogo3 < 0){
    lcd.clear();
    if(random(5) == 0 && flag1 == 0) posicao_fogo3 = 12;
  }
  
  pontos++;
  flag1 = 0;


}

void pontuacao(void){
  
  //SISTEMA DE PONTUACAO
  
    lcd.setCursor(13,0);
    lcd.print("PTS");
    lcd.setCursor(13,1);
    lcd.print(pontos);
}

void colisao(void){

    //LÓGGICA DO SITEMA DE COLISÃO
    
    if((posicao_boneco == 1 && posicao_fogo == 0) || (posicao_boneco == 0 && posicao_balao == 0)) flag2 = 1;
    if((posicao_boneco == 1 && posicao_fogo2 == 0) || (posicao_boneco == 0 && posicao_balao2 == 0)) flag2 = 1;
    if((posicao_boneco == 1 && posicao_fogo3 == 0) || (posicao_boneco == 0 && posicao_balao3 == 0)) flag2 = 1;
    if(flag2 == 1){  
        flag2 = 0;
        flag3 = 0; // flag da funcao de inicio
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("VOCE PERDEU");
        lcd.setCursor(0,1);
        lcd.print("Recomecar");
        pontuacao();
        delay(3000);   
        while(digitalRead(botao1) == HIGH);
        posicao_balao = 15;
        posicao_fogo = 9;
        posicao_boneco = 1;
        pontos = -1;
    }
}


void iniciar(void){
        if(flag3 == 0){
            flag3 = 1;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("INICIAR");      
            pontuacao();
            delay(3000);   
            while(digitalRead(botao1) == HIGH);
        }
}
