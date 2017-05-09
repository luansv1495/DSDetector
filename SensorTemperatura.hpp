#ifndef SENSORTEMPERATURA_HPP
#define SENSORTEMPERATURA_HPP

//------------------------------BIBLIOTECAS-----------------------------------------------
#include <OneWire.h>
#include <DallasTemperature.h>

//------------------------------CLASSE----------------------------------------------------
class SensorTemperatura{//Classe
   public:
      SensorTemperatura();//Contrutor recebendo parametro pino
      ~SensorTemperatura();//Destrutor
      bool verificarSensorTemp(DallasTemperature sensors,DeviceAddress sensor1);//Verificar se o sensor de temperatura está conectado
      float getTempMin();//Pegar Temperatura Minima
      float getTempMax();//Pegar Temperatura Atual
      float getTempAtual();//Pegar Temperatura Atual
      void setTempMin(float tempMin);//Inserir Temperatura Minima
      void setTempMax(float tempMax);//Inserir Temperatura Maxima
      void celsius(DallasTemperature sensors,DeviceAddress sensor1);//Pegar a temperatura do ambiente e inserir temperatura maxima, minima e atual
      void imprimirTemp(); //Imprimir informações adquiridas pelo sensor de temperatura
  private:
      float tempMin=999;
      float tempMax=0;
      float tempAtual=0;
};

//------------------------------METODOS---------------------------------------------------

float SensorTemperatura::getTempMin(){//Pegar Temperatura Minima
  return this->tempMin;//retorna valor da temperatura minima
}

float SensorTemperatura::getTempAtual(){//Pegar Temperatura Atual
  return this->tempAtual;//retorna valor da temperatura atual
}

float SensorTemperatura::getTempMax(){//Pegar Temperatura Maxima
  return this->tempMax;//retorna valor da temperatura maxima
}

void  SensorTemperatura::setTempMax(float tempMax){//Inserir Temperatura Maxima
  this->tempMax = tempMax;//insere o novo valor da temperatura maxima
}

void  SensorTemperatura::setTempMin(float tempMin){//Inserir Temperatura Minima
  this->tempMin = tempMin;//insere o novo valor da temperatura minima
}

bool SensorTemperatura::verificarSensorTemp(DallasTemperature sensors, DeviceAddress sensor1){//Verificar se o sensor de temperatura está conectado
  if(!sensors.getAddress(sensor1,0)){//Pesquisa se a sensor conectado caso não encontrar
      Serial.println("Sensor de Temperatura nao encontrado!");
      Serial.println();
      return false;//retorna falso caso não encontrar sensor
  }else{//Sensor encontrado
      Serial.println("Sensor de Temperatura encontrado!");
      //Serial.println();
      return true;//retorna verdade caso encontrar o sensor
  } 
}

void SensorTemperatura::celsius(DallasTemperature sensors,DeviceAddress sensor1){//Pegar a temperatura do ambiente e inserir temperatura maxima, minima e atual
    sensors.requestTemperatures();//Metodo para obter a temperatura
    float tempCelsius = sensors.getTempC(sensor1);//Metodo para obter a temperatura em celsius
    if(tempCelsius<this->tempMin){//se o valor lido for menor que a temperatura minima
      this->tempMin = tempCelsius;//insere a nova temperatura minima
    }
    if(tempCelsius>this->tempMax){//se o valor lido for maior que a temperatura maxima
        this->tempMax = tempCelsius;//insere a nova temperatura maxima
    }
    this->tempAtual = tempCelsius;//insere a temperatura atual
}

void SensorTemperatura::imprimirTemp(){//Imprimir informações adquiridas pelo sensor de temperatura
  Serial.print("Temperatura: ");
  Serial.print(getTempAtual());//pega valor da temperatura atual
  Serial.print("ºC Min: ");
  Serial.print(getTempMin());//pega valor da temperatura minima
  Serial.print("ºC Max: ");
  Serial.print(getTempMax());//pega valor da temperatura maxima
  Serial.println("ºC");
}

#endif

