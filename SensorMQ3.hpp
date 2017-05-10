#ifndef SENSORMQ3_HPP
#define SENSORMQ3_HPP

//------------------------------BIBLIOTECAS-----------------------------------------------
  #include <string.h>
//------------------------------CLASSE----------------------------------------------------
class SensorMQ3{//Classe
   public:
       SensorMQ3();//Contrutor recebendo parametro pino
       ~SensorMQ3();//Destrutor
       int getVAtual();
       int getVMin();
       int getVMax();
       void setVAtual(int vAtual);
        void setVMin(int vMin);
         void setVMax(int vMax);
       void imprimirMQ3();
       void sensorGas(int pinoMQ3);
  private:
    int pinoMQ3=0;  
    int vMin=999;
    int vMax=0;
    int vAtual=0;
};

SensorMQ3::SensorMQ3(){}
SensorMQ3::~SensorMQ3(){}

void SensorMQ3::sensorGas(int pinoMQ3){
    int v1 = analogRead(A13);
    if(v1<this->vMin){//se o valor lido for menor que a temperatura minima
      this->vMin = v1;//insere a nova temperatura minima
    }
    if(v1>this->vMax){//se o valor lido for maior que a temperatura maxima
        this->vMax = v1;//insere a nova temperatura maxima
    }
    this->vAtual = v1;//insere a temperatura atual
}

int SensorMQ3::getVAtual(){
  return vAtual;
}

void SensorMQ3::setVAtual(int vAtual){
  this->vAtual = vAtual;
}

int SensorMQ3::getVMin(){
  return vMin;
}

void SensorMQ3::setVMin(int vAtual){
  this->vMin = vMin;
}

int SensorMQ3::getVMax(){
  return vMax;
}

void SensorMQ3::setVMax(int vMax){
  this->vMax = vMax;
}

void SensorMQ3::imprimirMQ3(){
     Serial.print("MQ3: ");
  Serial.print(getVAtual());//pega valor da temperatura atual
  Serial.print(" Min: ");
  Serial.print(getVMin());//pega valor da temperatura minima
  Serial.print(" Max: ");
  Serial.println(getVMax());//pega valor da temperatura maxima
}

#endif

