/*
//Programa : DSDetector
//Autor : Maycon Rafael Campos Borba
*/

//------------------BIBLIOTECAS---------
#include "SensorTemperatura.hpp"
#include "SensorMQ3.hpp"
#include "Sistem.hpp"
#include "Lcd.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>  
#include <NewTone.h> 

//-----------------PINOS-----------------
  const int buzzer = 3;
  const int rele = 10;
  const int led = 11;
  const int botao = 12;
  const int pinoTemperatura = 13;
  const int pinoLcd= 0;
  const int pinoMQ3 = 1;
//-------Caracteres LCD proprios---------
byte Carregando[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

    
//----------------VARIAVEIS---------------
 int frequenciaBuzzer = 1500;
//----------------PONTEIROS---------------
  SensorTemperatura *sensorTemp;
  DSDetector *sistemaMetodos;
  SensorMQ3 *sensorMQ;
  Lcd *tela;
  LiquidCrystal lcd(8,//d1
                    9,//d0
                    4,//d5
                    5,//d4
                    6,//d3
                    7);//d2
  OneWire oneWire(pinoTemperatura);
  DallasTemperature sensors(&oneWire);
  DeviceAddress sensor1;

//-----------------SETUP-------------------
void setup(){
  Serial.begin(9600);
  sensors.begin();
  lcd.createChar(0,Carregando);  
  lcd.begin(16,2);
  sensorTemp = new SensorTemperatura();
  sistemaMetodos = new DSDetector();
  sensorMQ = new SensorMQ3();
  tela = new Lcd(pinoLcd);
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(rele,OUTPUT);
  pinMode(botao,INPUT);
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
  sensorTemp->celsius(sensors,sensor1);
  if(sensorTemp->getTempAtual()<=19){
    tela->carregar(lcd,7500);//2min
  }else if(sensorTemp->getTempAtual()>19
  and sensorTemp->getTempAtual()<=27){
     tela->carregar(lcd,4375);//1min 10s
  }else{
     tela->carregar(lcd,9375);
  }
   lcd.setCursor(0,0);
  lcd.print("Para assoprar");
   lcd.setCursor(0,1);
   lcd.print("botao select");
  if(tela->escolhaButton()==5){
        delay(3000);
        lcd.clear();
        sensorTemp->celsius(sensors,sensor1);
        sensorTemp->imprimirTemp();
        sensorMQ->sensorGas(pinoMQ3);
        sensorMQ->imprimirMQ3();   
        lcd.setCursor(0,0);
        lcd.print("Temperatura:");
        lcd.print((int)sensorTemp->getTempAtual());
        lcd.print(" C");
        lcd.setCursor(0,1);
        lcd.print("MQ3:");
        lcd.print(sensorMQ->getVAtual());
        delay(3000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Resultado:");
        lcd.setCursor(0,1);
        lcd.print(
        sistemaMetodos->bebado(sensorMQ->getVAtual()
		,rele,(int)sensorTemp->getTempAtual(),
		sensorMQ->getVMax()));
        delay(1000);//
  }
}

//---------------------LOOP-------------------------
void loop(){
 if(sistemaMetodos->sistemaEstado(led,botao)){
           lcd.clear();
           sensorTemp->celsius(sensors,sensor1);
           sensorMQ->sensorGas(pinoMQ3);
           lcd.setCursor(0,0);
           lcd.print("Temperatura:");
           lcd.print((int)sensorTemp->getTempAtual());
           lcd.print(" C");
           lcd.setCursor(0,1);
           lcd.print("MQ3:");
           lcd.print(sensorMQ->getVAtual());
           delay(3000);
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("Resultado:");
           lcd.setCursor(0,1);
          lcd.print(
sistemaMetodos->bebado(sensorMQ->getVAtual(),rele,
(int)sensorTemp->getTempAtual(),sensorMQ->getVMax()));
           if((int)sensorTemp->getTempAtual()<=19){
            delay(150000);
           }else if((int)sensorTemp->getTempAtual()>19
		   and (int)sensorTemp->getTempAtual()<27){
            delay(120000);
           }else{
            delay(145000);
           }
  }else{
       lcd.clear();
       lcd.setCursor(4,0);
       lcd.print("Sistema");
       lcd.setCursor(3,1);
       lcd.print("Desligado!");
       NewTone(buzzer, frequenciaBuzzer); 
       digitalWrite(rele, HIGH);
       delay(100);
       noNewTone(buzzer);
       delay(2000);
  }

}


