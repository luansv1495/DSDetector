/*
//Programa : DSDetector
//Autor : Maycon Rafael Campos Borba
*/

//------------------------------BIBLIOTECAS-----------------------------------------------
#include "SensorTemperatura.hpp"
#include "SensorMQ3.hpp"
#include "DSDetector.hpp"
#include "Lcd.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>  
#include <NewTone.h> 

//------------------------------PINOS-----------------------------------------------------
  const int buzzer = 3;
  const int rele = 10;
  const int led = 11;//Pino Led
  const int botao = 12;//Pino Botão
  const int pinoTemperatura = 13;//Pino Temperatura
  const int pinoLcd= 0;//A0
  const int pinoMQ3 = 1;//A1
//------------------------------Caracteres LCD proprios-----------------------
byte Carregando[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

    
//------------------------------VARIAVEIS-------------------------------------------------
 int frequenciaBuzzer = 1500;
//------------------------------PONTEIROS-------------------------------------------------
  SensorTemperatura *sensorTemp;//Criando ponteiro para metodos da classe sensor de temperatura
  DSDetector *sistemaMetodos;//Criando ponteiro para metodos do sistema
  SensorMQ3 *sensorMQ;
  Lcd *tela;
  LiquidCrystal lcd(8,//d1
                    9,//d0
                    4,//d5
                    5,//d4
                    6,//d3
                    7);//d2
  OneWire oneWire(pinoTemperatura);//Define uma instancia do oneWire para comunicacao com o sensor
  DallasTemperature sensors(&oneWire);//passando como referencia oneWire para DallasTemperature
  DeviceAddress sensor1;//Arrays para armazenar endereços de dispositivo(sensores)

//------------------------------SETUP-----------------------------------------------------
void setup(){
  Serial.begin(9600);//iniciando porta serial na velocidade 9600 padrão de varios sensores
  sensors.begin();//iniciando a biblioteca DallasTemperature
  lcd.createChar(0,Carregando);  
  lcd.begin(16,2);
  sensorTemp = new SensorTemperatura();
  sistemaMetodos = new DSDetector();
  sensorMQ = new SensorMQ3();
  tela = new Lcd(pinoLcd);
  pinMode(led,OUTPUT);//definindo pino led como saida
  pinMode(buzzer,OUTPUT);
  pinMode(rele,OUTPUT);
  pinMode(botao,INPUT);//definindo pino botao como entrada
  pinMode(pinoMQ3,INPUT);
  digitalWrite(rele, HIGH);
  lcd.setCursor(2,0);
  lcd.print("Bem-vindo ao");
  lcd.setCursor(3,1);
  lcd.print("DSDetector");
  delay(2496);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("AGUARDE...");
  delay(2496);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aquecendo sensor");
  tela->carregar(lcd,3439);//5344
  sensorTemp->celsius(sensors,sensor1);
  sensorTemp->imprimirTemp();//imprimir resultados da temperatura
  sensorMQ->sensorGas(pinoMQ3);
  lcd.print(bebado(sensorMQ->getVAtual(),rele));
}

//------------------------------LOOP-----------------------------------------------------
void loop(){
  //tela->menuLCD(lcd);
 if(sistemaMetodos->sistemaEstado(led,botao)){//Verificar se o sistema está ligado
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Temperatura:");
         lcd.print((int)sensorTemp->getTempAtual());
         lcd.print(" C");
         lcd.setCursor(0,1);
         lcd.print("MQ3:");
         lcd.print(sensorMQ->getVAtual());
         delay(1000);
        
         if(tela->escolhaButton()==5){ //
          lcd.clear();
           sensorTemp->celsius(sensors,sensor1);
           sensorTemp->imprimirTemp();//imprimir resultados da temperatura
           sensorMQ->sensorGas(pinoMQ3);
          
           sensorMQ->imprimirMQ3();   
           lcd.setCursor(0,0);
           lcd.print("Temperatura:");
           lcd.print((int)sensorTemp->getTempAtual());
           lcd.print(" C");
           lcd.setCursor(0,1);
           lcd.print("MQ3:");
           lcd.print(sensorMQ->getVAtual());
           delay(1000);
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("Resultado:");
           lcd.setCursor(0,1);
           lcd.print(bebado(sensorMQ->getVAtual(),rele));
           delay(1000);// reexecutar a cada 1 segundo
         }
         
       
  }else{//Se o sitema estiver desligado
       lcd.clear();
       lcd.setCursor(4,0);
       lcd.print("Sistema");
       lcd.setCursor(3,1);
       lcd.print("Desligado!");
       NewTone(buzzer, frequenciaBuzzer); 
       digitalWrite(rele, HIGH);
       delay(100);
       noNewTone(buzzer);
       delay(1000);//reexecutar a cada 2 segundo
  }

}
