#ifndef SENSORTEMPERATURA_HPP
#define SENSORTEMPERATURA_HPP
//--------------------------------------------------------------------------
#include <OneWire.h>
#include <DallasTemperature.h>
//--------------------------------------------------------------------------
class SensorTemperatura{
   public:
      SensorTemperatura(int pino);
      bool verificarSensorTemp(DallasTemperature sensors,DeviceAddress sensor1);
      void mostrarEndereco(DeviceAddress sensor1);
      float getTempMin();
      float getTempMax();
      float getTempAtual();
      void setTempMin(float tempMin);
      void setTempMax(float tempMax);
      void celsius(DallasTemperature sensors,DeviceAddress sensor1);
      void imprimirTemp(); 
  private:
    float tempMin;
    float tempMax;
    float tempAtual;
    int pino;
};

SensorTemperatura::SensorTemperatura(int pino){
      this->pino = pino;
      this->tempMin=999;
      this->tempMax=0;
}

float SensorTemperatura::getTempMin(){
  return this->tempMin;
}

float SensorTemperatura::getTempAtual(){
  return this->tempAtual;
}

float SensorTemperatura::getTempMax(){
  return this->tempMax;
}

void  SensorTemperatura::setTempMax(float tempMax){
  this->tempMax = tempMax;
}

void  SensorTemperatura::setTempMin(float tempMin){
  this->tempMin = tempMin;
}

 bool SensorTemperatura::verificarSensorTemp(DallasTemperature sensors, DeviceAddress sensor1){
  if(!sensors.getAddress(sensor1,0)){
    Serial.println("Sensor de Temperatura nao encontrado!");
    Serial.println();
    return false;
  }else{
    Serial.println("Sensor de Temperatura encontrado!");
    Serial.print("Endereco: ");
    mostrarEndereco(sensor1);
     Serial.println();
    return true;
  }
  
 }

 void SensorTemperatura::mostrarEndereco(DeviceAddress sensor1){
    for(uint8_t i=1; i<8;i++){
      if(sensor1[i]<16){
        Serial.print("0");
      }else{
        Serial.print(sensor1[i],HEX);
      }
    }
 }

void SensorTemperatura::celsius(DallasTemperature sensors,DeviceAddress sensor1){
    sensors.requestTemperatures();
    float tempCelsius = sensors.getTempC(sensor1);
    if(tempCelsius<this->tempMin){
      this->tempMin = tempCelsius;
    }
    if(tempCelsius>this->tempMax){
        this->tempMax = tempCelsius;
    }
    this->tempAtual = tempCelsius;
 }

void SensorTemperatura::imprimirTemp(){
  Serial.print("Temperatura: ");
  Serial.print(getTempAtual());
  Serial.print("ºC Min: ");
  Serial.print(getTempMin());
  Serial.print("ºC Max: ");
  Serial.print(getTempMax());
   Serial.println("ºC");
}
#endif

