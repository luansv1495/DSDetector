#ifndef INCLUDES_HPP
#define INCLUDES_HPP
//--------------------------------------------------------------------------
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  //Vem no Arduino já
#include <Arduino.h>
//--------------------------------------------------------------------------
class Includes{
   public:
      Includes(int pinoSensorTemperatura);
      int getPinoSensorTemperatura();
  private:
    int _pinoSensorTemperatura;
 
};

Includes::Includes(int pinoSensorTemperatura){
  _pinoSensorTemperatura = pinoSensorTemperatura;
}

int Includes::getPinoSensorTemperatura(){
  return this->_pinoSensorTemperatura;
}
#endif


