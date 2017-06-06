#ifndef DSDETECTOR_HPP
#define DSDETECTOR_HPP

//------------------------------BIBLIOTECAS-----------------------------------------------

//------------------------------CLASSE----------------------------------------------------
class DSDetector{//Classe
   public:
      DSDetector();//Contrutor
      ~DSDetector();//Destrutor
     bool sistemaEstado(int led,int botao);//Verificar se sitema esta desligado ou ligado
     int getValorAjuste();
     String bebado(int vAtual,int rele,int varianca,int vMax);
     void ajuste(int varianca,int vMax);
     
  private:
  int valorAjuste = 0;
};

//------------------------------METODOS---------------------------------------------------
DSDetector::DSDetector(){//Contrutor
}

DSDetector::~DSDetector(){//Destrutor
}

int DSDetector::getValorAjuste(){
  return valorAjuste;
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

void DSDetector::ajuste(int varianca,int vMax){
  if(vMax<=160){
    if(varianca <=19){
      valorAjuste = 75;
    }else if(varianca>19 and varianca<27){
      valorAjuste = 65;
    }else{
      valorAjuste = 90;
    }
  }else{
     if(varianca <=19){
        valorAjuste = 79;
    }else if(varianca>19 and varianca<27){
        valorAjuste = 84;
    }else{
        valorAjuste = 104;
    }
  }
}

String DSDetector::bebado(int vAtual,int rele,int varianca,int vMax){
  ajuste(varianca,vMax);
  if(vAtual <= getValorAjuste()){
     digitalWrite(rele, LOW);
      return "Voce nao bebeu...";
   }else{
      digitalWrite(rele, HIGH);// desliga o veiculo
      return "Voce esta bebado";
  }
}

#endif
