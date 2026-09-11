// Nesse projeto inicial feito no TinkerCad, não possúi todos os componentes
// Então usaremos outros para sua representação.
// O Arduíno representa o ESP32.
// Sensor de temperatura representa o sensor MAX30102.
// A tela LCD 16 x 2(I2C) representa a o Display OLED 0,96". 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Identificação da tela.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declaração da variavel que ira servir de exemplo para o sensor cardiaco.
int sensor = 0, batimentos = 0;

// Declaração do buzzer e de sua variavel auxiliar.
const int buzzer = 13;
int  buzzer_loop = 0;

const int led_R = 2, led_G = 3, led_B = 4;

// Declaração de funcões que serão usadas no decorrer do código.
void verificacao_buzzer();
void verificacao_led();
void mostrar_tela();

void setup()
{
  // Declarando o buzzer como saída.
  pinMode(buzzer, OUTPUT);
  // Declarando a entrada do sensor que simboliza o sensor cardiaco.
  pinMode(A0, INPUT);
  // Declarando os leds como entradas.
  pinMode(led_R, INPUT);
  pinMode(led_G, INPUT);
  pinMode(led_B, INPUT);
  
  Serial.begin(9600);

  // Iniciação da tela.
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Batimentos:");
}

void loop()
{
  // Recebe os dados do sensor e os converte em batimentos.
  sensor = analogRead(A0);
  batimentos = map((sensor * 3), 0, 1023, 0, 160);
  
  // Funcões auxiliares
  verificacao_buzzer();
  verificacao_led();
  mostrar_tela();

  /*Serial.print("Sensor: ");
  Serial.println(sensor);

  Serial.print("Batimentos: ");
  Serial.println(batimentos);*/


  delay(1000);
}

// Verifica o número de batimentos para ativar o buzzer.
void verificacao_buzzer() {
  // caso verdade ativa um som para alertar o usúario.
  if((batimentos > 110 || batimentos < 40) && buzzer_loop == 0){
  	tone(buzzer, 1000);
    buzzer_loop = 1;
  }
  // desativa o buzzer se ainda estiver ligado.
  else{
  	noTone(buzzer);
    buzzer_loop = 0;
  }
}

// Verifica o número de batimentos e altera a cor do led de acordo com ele.
void verificacao_led(){
  // caso verdade da a saída da cor vermelha(representando perigo).
  if(batimentos > 110 || batimentos < 40){
    digitalWrite(led_R, HIGH);
    digitalWrite(led_G, LOW);
    digitalWrite(led_B, LOW);
  }
   // caso verdade da a saída da cor rosa(representando inicio de perigo).
  else if(batimentos > 90 || batimentos < 50){
    digitalWrite(led_R, HIGH);
    digitalWrite(led_G, LOW);
    digitalWrite(led_B, HIGH);
  }
  // Saída da cor verde(representando normalidade).
  else {
    digitalWrite(led_R, LOW);
    digitalWrite(led_G, HIGH);
    digitalWrite(led_B, LOW);
  }
}

// mostra na tela o número de batimentos por minuto.
void mostrar_tela(){
  
  lcd.setCursor(0, 1);
  lcd.print("BPM: ");
  lcd.print(batimentos);
  lcd.print("    ");
  
}