/*
//Programa : DSDetector
//Autor : Maycon Rafael Campos Borba
*/

//------------------------------BIBLIOTECAS-----------------------------------------------
#include "SensorTemperatura.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Arduino.h>

//------------------------------PINOS-----------------------------------------------------
 int PinoTemperatura = 13;//Pino Temperatura
 
//----------------------------------------------------------------------------------------
  Includes *v1;
 
//------------------------------Iniciando Sensor Temperatura
 /* OneWire sensorTemp(getPinoSensorTemperatura());
  DallasTemperature sensors(sensorTemp);
  DeviceAddress sensor1;*/
//---------------------------------------------------------------------------------------
void setup(){
  v1 = new Includes();
  v1->setPinoSensorTemperatura(13);
  //Serial.begin(9600);
 // sensors.begin();
}
void loop(){

}
