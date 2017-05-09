#ifndef SENSORMQ3_HPP
#define SENSORMQ3_HPP

//------------------------------BIBLIOTECAS-----------------------------------------------

//------------------------------CLASSE----------------------------------------------------
class SensorMQ3{//Classe
   public:
       SensorMQ3();//Contrutor recebendo parametro pino
       ~SensorMQ3();//Destrutor
       void setValor(int valor);
       int getValor();
       void imprimirMQ3();
       void setPinoMQ3(const char pinoMQ3[]);
  private:
    int valor; 
    char pinoMQ3;   
    
};


int SensorMQ3::getValor(){
  return valor;
}

void SensorMQ3::setValor(int valor){
  this->valor = valor;
}


void SensorMQ3::setPinoMQ3(const char pinoMQ3[]){
  
}



void SensorMQ3::imprimirMQ3(){
  Serial.println(getValor());
}

#endif

