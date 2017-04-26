#ifndef SENSORTEMPERATURA_HPP
#define SENSORTEMPERATURA_HPP
//--------------------------------------------------------------------------
#include "Includes.hpp"

//--------------------------------------------------------------------------
class SensorTemperatura{
   public:
      SensorTemperatura();
      void IniciaSensorTemp();
      void VerificaSensor();
  private:
    float tempMin = 999;
    float tempMax = 0;
    float tempAtual = 0;
};

SensorTemperatura::SensorTemperatura(){
}

void SensorTemperatura::IniciaSensorTemp(){
  //OneWire sensorTemp(Includes->getPinoSensorTemperatura());
  DallasTemperatura sensors(sensorTemp);
}

void SensorTemperatura::VerificaSensor(){
 
}

#endif

