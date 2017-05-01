/*
//Programa : DSDetector
//Autor : Maycon Rafael Campos Borba
*/

//------------------------------BIBLIOTECAS-----------------------------------------------
#include "SensorTemperatura.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>

//------------------------------PINOS-----------------------------------------------------
  const int pinoTemperatura = 13;//Pino Temperatura
  const int led = 11;//Pino Led
  const int botao = 12;//Pino Botão
//------------------------------VARIAVEIS-------------------------------------------------
  int estadoBotao = 0;//Estado do botão
  int limpar = 0;
//------------------------------PONTEIROS-------------------------------------------------
  SensorTemperatura *sensorTemp;
  OneWire oneWire(pinoTemperatura);
  DallasTemperature sensors(&oneWire);
  DeviceAddress sensor1;
//------------------------------METODOS---------------------------------------------------
bool sistemaEstado();
void limparTela(int limpar);
//------------------------------SETUP-----------------------------------------------------
void setup(){
  sensorTemp = new SensorTemperatura(pinoTemperatura);
  Serial.begin(9600);
  sensors.begin();
  pinMode(led,OUTPUT);
  pinMode(botao,INPUT);

}

//------------------------------LOOP-----------------------------------------------------
void loop(){
 if(!sistemaEstado()){
    limparTela(limpar);
    limpar=0;
 }else{
    if(sensorTemp->verificarSensorTemp(sensors,sensor1)){
         sensorTemp->celsius(sensors,sensor1);
         sensorTemp->imprimirTemp();
         limpar = 1;   
    }else{//se não encontrar o sensor
      sensorTemp->setTempMax(0);
      sensorTemp->setTempMin(999);
      delay(500);
    }
 }
  delay(500);
}
bool sistemaEstado(){//Verifica se o sistema está ligado
  estadoBotao = digitalRead(botao);
  if(estadoBotao==HIGH){
      digitalWrite(led,HIGH);
      return true;
  }else{
      digitalWrite(led,LOW);
      return false;
  } 
}

void limparTela(int limpar){//Limpa a tela
  if(limpar!=0){
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n");
  }
}

