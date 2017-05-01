#ifndef SENSORTEMPERATURA_HPP
#define SENSORTEMPERATURA_HPP

//------------------------------BIBLIOTECAS-----------------------------------------------
#include <OneWire.h>
#include <DallasTemperature.h>

//------------------------------CLASSE----------------------------------------------------
class SensorTemperatura{
   public:
      SensorTemperatura(int pino);
      ~SensorTemperatura();
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

//------------------------------METODOS---------------------------------------------------
SensorTemperatura::SensorTemperatura(int pino){//Contrutor
      this->pino = pino;
      this->tempMin=999;
      this->tempMax=0;
}

SensorTemperatura::~SensorTemperatura(){
}

float SensorTemperatura::getTempMin(){//Pegar Temperatura Minima
  return this->tempMin;
}

float SensorTemperatura::getTempAtual(){//Pegar Temperatura Atual
  return this->tempAtual;
}

float SensorTemperatura::getTempMax(){//Pegar Temperatura Maxima
  return this->tempMax;
}

void  SensorTemperatura::setTempMax(float tempMax){//Inserir Temperatura Maxima
  this->tempMax = tempMax;
}

void  SensorTemperatura::setTempMin(float tempMin){//Inserir Temperatura Minima
  this->tempMin = tempMin;
}

bool SensorTemperatura::verificarSensorTemp(DallasTemperature sensors, DeviceAddress sensor1){//Verificar se o sensor de temperatura está conectado
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

void SensorTemperatura::mostrarEndereco(DeviceAddress sensor1){//Mostrar o endereco do sensor de temperatura
    for(uint8_t i=1; i<8;i++){
      if(sensor1[i]<16){
        Serial.print("0");
      }else{
        Serial.print(sensor1[i],HEX);
      }
    }
}

void SensorTemperatura::celsius(DallasTemperature sensors,DeviceAddress sensor1){//Pegar a temperatura do ambiente e inserir temperatura maxima, minima e atual
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

void SensorTemperatura::imprimirTemp(){//Imprimir informações adquiridas pelo sensor de temperatura
  Serial.print("Temperatura: ");
  Serial.print(getTempAtual());
  Serial.print("ºC Min: ");
  Serial.print(getTempMin());
  Serial.print("ºC Max: ");
  Serial.print(getTempMax());
  Serial.println("ºC");
}



#endif

