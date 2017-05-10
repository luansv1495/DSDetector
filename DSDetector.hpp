#ifndef DSDETECTOR_HPP
#define DSDETECTOR_HPP

//------------------------------BIBLIOTECAS-----------------------------------------------

//------------------------------CLASSE----------------------------------------------------
class DSDetector{//Classe
   public:
      DSDetector();//Contrutor
      ~DSDetector();//Destrutor
     bool sistemaEstado(int led,int botao);//Verificar se sitema esta desligado ou ligado
  private:
};

//------------------------------METODOS---------------------------------------------------
DSDetector::DSDetector(){//Contrutor
}

DSDetector::~DSDetector(){//Destrutor
}

bool DSDetector::sistemaEstado(const int led,const int botao){//Verifica se o sistema está ligado ou desligado
  int estadoBotao = digitalRead(botao);//verifica se botao esta ligado ou desligado
  if(estadoBotao==HIGH){//se botao estiver ligado
      digitalWrite(led,HIGH);//acender o led
      return true;//retornar verdade
  }else{//se botao estiver desligado
      digitalWrite(led,LOW);//apagar o led
      return false;//retornar falso
  } 
}

#endif
