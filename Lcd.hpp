#ifndef LCD_HPP
#define LCD_HPP
//------------------------------BIBLIOTECAS-----------------------------------------------
 #include <LiquidCrystal.h> 
 #include <string.h>
//------------------------------CLASSE----------------------------------------------------
class Lcd{//Classe
   public:
       Lcd(int pinoLcd);//Contrutor recebendo parametro pino
       ~Lcd();//Destrutor
        int escolhaButton();
        void imprimirButton(LiquidCrystal lcd);
        int menuLCD(LiquidCrystal lcd);
        void carregar(LiquidCrystal lcd,int tempo);
  private:
    int pinoLcd;
    int button;
};

Lcd::Lcd(int pinoLcd){
  this->pinoLcd = pinoLcd;
  }
Lcd::~Lcd(){}

int Lcd::escolhaButton(){
  button = analogRead(pinoLcd);
  if(button>=100 && button<=160){
    //up
   this->button=1;
   return 1;
  }else if(button>=260 && button<=360){
    //down
      this->button=2;
      return 2;
  }else if(button>=400 && button<=560){
    //left
     this-> button=3;
     return 3;
  }else if(button>=0 && button<=75){
    //right
      this->button=4;
      return 4;
  }else if(button>=600 && button<=780){
    //select
      this->button=5;
      return 5;
  }else{
    return escolhaButton();
  }
}

void Lcd::imprimirButton(LiquidCrystal lcd){
 lcd.setCursor(0,0);
 lcd.print("Tecla apertada:");
 lcd.setCursor(0,1); 
 switch(button){
  case 1:{
     lcd.print("Cima");
  }break;
  case 2:{
    lcd.print("Baixo");
  }break;
  case 3:{
    lcd.print("Esquerda");
  }break;
  case 4:{
    lcd.print("Direita");
  }break;
  case 5:{
    lcd.print("Select");
  }break;
  default:{
    lcd.print("Invalida");
  }
 }
}

void Lcd::carregar(LiquidCrystal lcd,int tempo){
  for(int i=0;i<=16;i++){
        lcd.setCursor(i,1);
        lcd.write(byte(0));
        delay(tempo);
    }
     lcd.clear();
}


int Lcd::menuLCD(LiquidCrystal lcd){
  int menu=1,v1=0,escolha=0,v2=1,cont=1,opcao;
  String opcoes[2];
   opcoes[0] = "0 - Sair."; 
   opcoes[1] = "1 - Wireless."; 
   lcd.clear();
   lcd.print("Teclas menu:");
   lcd.setCursor(0,1);
   lcd.print("Up,Down,Select");
   delay(2700);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Menu Opcoes:");
   carregar(lcd,100);  
   
   do{
     lcd.setCursor(0,0);
     lcd.print(opcoes[v1]); 
     lcd.setCursor(0,1);
     lcd.print(opcoes[v2]);
     opcao = escolhaButton();
     delay(300);
     Serial.print("v1:");
      Serial.println(v1);
      Serial.print("v2:");
      Serial.println(v2);
      Serial.print("cont:");
      Serial.println(cont);
      Serial.print("op:");
      Serial.println(opcao);
     if(opcao == 1 || opcao == 2 || opcao == 5){
     if(opcao == 1 && cont==1){opcao = 2; cont = 0;}
     if(opcao == 2 && cont==2){opcao = 1; cont = 0;}
     if(opcao==1){
        v1=0;
        v2=1;
        cont=1;
     }else if(opcao==2){
        v1=1;
        v2=0;
        cont=2;
     }else if(opcao==5){
       escolha= v2;
       menu=0;
     }
     lcd.clear();
     
     }
  }while(menu!=0);
   if(escolha==0){
       lcd.setCursor(0,0);
       lcd.print("Saindo do Menu");
       carregar(lcd,525);
   }else{
       lcd.setCursor(0,0);
       lcd.print("Wireless");
       delay(525);
       lcd.clear();
   }
  delay(250);
}
#endif

