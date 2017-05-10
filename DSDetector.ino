/*
//Programa : DSDetector
//Autor : Maycon Rafael Campos Borba
*/

//------------------------------BIBLIOTECAS-----------------------------------------------
#include "SensorTemperatura.hpp"
#include "SensorMQ3.hpp"
#include "DSDetector.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>

//------------------------------PINOS-----------------------------------------------------
  const int pinoTemperatura = 13;//Pino Temperatura
  const int led = 11;//Pino Led
  const int botao = 12;//Pino Botão
  const int pinoMQ3 = 13;
    
//------------------------------VARIAVEIS-------------------------------------------------

//------------------------------PONTEIROS-------------------------------------------------
  SensorTemperatura *sensorTemp;//Criando ponteiro para metodos da classe sensor de temperatura
  DSDetector *sistemaMetodos;//Criando ponteiro para metodos do sistema
  SensorMQ3 *sensorMQ;
  OneWire oneWire(pinoTemperatura);//Define uma instancia do oneWire para comunicacao com o sensor
  DallasTemperature sensors(&oneWire);//passando como referencia oneWire para DallasTemperature
  DeviceAddress sensor1;//Arrays para armazenar endereços de dispositivo(sensores)

//------------------------------SETUP-----------------------------------------------------
void setup(){
  Serial.begin(9600);//iniciando porta serial na velocidade 9600 padrão de varios sensores
  sensors.begin();//iniciando a biblioteca DallasTemperature
  sensorTemp = new SensorTemperatura();
  sistemaMetodos = new DSDetector();
  sensorMQ = new SensorMQ3();
  pinMode(led,OUTPUT);//definindo pino led como saida
  pinMode(botao,INPUT);//definindo pino botao como entrada
  pinMode(pinoMQ3,INPUT);
  
  
}

//------------------------------LOOP-----------------------------------------------------
void loop(){
  if(sistemaMetodos->sistemaEstado(led,botao)){//Verificar se o sistema está ligado
      if(sensorTemp->verificarSensorTemp(sensors,sensor1)){//se encontrar o sensor
           sensorTemp->celsius(sensors,sensor1);//chamada da função para obter temperaturas
          sensorTemp->imprimirTemp();//imprimir resultados da temperatura
          sensorMQ->sensorGas(pinoMQ3);
          sensorMQ->imprimirMQ3();   
           delay(1000);// reexecutar a cada 1 segundo
       }else{//se não encontrar o sensor
            sensorTemp->setTempMax(0);//reseta valor maximo
            sensorTemp->setTempMin(999);//reseta valor minimo
            delay(1000);//reexecutar a cada 1 segundo
       }
  }else{//Se o sitema estiver desligado
       Serial.println("Sistema Desligado!");
       delay(2000);//reexecutar a cada 2 segundo
  }
}
