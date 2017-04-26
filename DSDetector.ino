/*
//Programa : DSDetector
//Autor : Maycon Rafael Campos Borba
*/

//------------------------------BIBLIOTECAS-----------------------------------------------
#include "SensorTemperatura.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>

//------------------------------PINOS-----------------------------------------------------
  int pinoTemperatura = 13;//Pino Temperatura
 
//------------------------------PONTEIROS-------------------------------------------------
  SensorTemperatura *sensorTemp;
  OneWire oneWire(pinoTemperatura);
  DallasTemperature sensors(&oneWire);
  DeviceAddress sensor1;
 
//------------------------------SETUP-----------------------------------------------------
void setup(){
  sensorTemp = new SensorTemperatura(pinoTemperatura);
  Serial.begin(9600);
  sensors.begin();
}

//------------------------------LOOP-----------------------------------------------------
void loop(){
  if(sensorTemp->verificarSensorTemp(sensors,sensor1)){
       sensorTemp->celsius(sensors,sensor1);
       sensorTemp->imprimirTemp();
   }
  delay(500);
}
