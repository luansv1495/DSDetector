#ifndef SENSORTEMPERATURA_HPP
#define SENSORTEMPERATURA_HPP
//--------------------------------------------------------------------------
#include "Includes.hpp"
#include <DallasTemperature.h>

//--------------------------------------------------------------------------
class SensorTemperatura{
   public:
      SensorTemperatura();
      void VerificaSensor();
  private:
    float tempMin = 999;
    float tempMax = 0;
    float tempAtual = 0;
};

SensorTemperatura::SensorTemperatura(){
}


void SensorTemperatura::VerificaSensor(){
 
}

#endif

