// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>                              //Biblioteca para o display LCD

// --- Mapeamento de Hardware ---



// --- Protótipo das Funções Auxiliares ---
void keyboardRead();
 


// --- Variáveis Globais ---
int adc_value = 0x00;                       //armazena o valor digital do conversor AD

boolean right  = 0x00, butt01 = 0x00,
        up     = 0x00, butt02 = 0x00,
        down   = 0x00, butt03 = 0x00,
        left   = 0x00, butt04 = 0x00,
        select = 0x00, butt05 = 0x00;
        
        
// --- Hardware do LCD ---
LiquidCrystal disp(8,  //RS no digital 8
                   9,  //EN no digital 9
                   4,  //D4 no digital 4
                   5,  //D5 no digital 5
                   6,  //D6 no digital 6
                   7); //D7 no digital 7
        
        
void setup()
{
     disp.begin(16,2);                                    //Inicializa LCD 16 x 2
     disp.setCursor(1,0);                                 //Posiciona cursor na coluna 2, linha 1
     disp.print("Teclado Analog");                        //Imprime mensagem

} //end setup

void loop()
{
  keyboardRead();
  
    if(right == 0x01)                              //tecla right pressionada?
    {                                              //sim...
      right = 0x00;                                //limpa flag da tecla
      disp.setCursor(0,1);                         //Posiciona cursor na coluna 1, linha 2
      disp.print("  right         ");              //Imprime mensagem
    
    } //end if right

    if(up == 0x01)                                 //tecla up pressionada?
    {                                              //sim...
      up = 0x00;                                   //limpa flag da tecla
      disp.setCursor(0,1);                         //Posiciona cursor na coluna 1, linha 2
      disp.print("  up            ");              //Imprime mensagem
    
    } //end if up
    
    if(down == 0x01)                               //tecla down pressionada?
    {                                              //sim...
      down = 0x00;                                 //limpa flag da tecla
      disp.setCursor(0,1);                         //Posiciona cursor na coluna 1, linha 2
      disp.print("  down          ");              //Imprime mensagem
    
    } //end if down
    
    if(left == 0x01)                               //tecla left pressionada?
    {                                              //sim...
      left = 0x00;                                 //limpa flag da tecla
      disp.setCursor(0,1);                         //Posiciona cursor na coluna 1, linha 2
      disp.print("  left          ");              //Imprime mensagem
    
    } //end if left
    
   
    

} //end loop



/*************************************************************************

      FUNÇÃO PARA LEITURA DO TECLADO ANALÓGICO

Leu-se as respectivas tensões geradas na saída do teclado, para cada botão
obtendo-se a seguinte tabela:


      VALORES AD REPRESENTADOS PELAS TECLAS:

       num |  Nome   | Tensão (V) | Digital
      --------------------------------------
       01  |  right  |  0,0000    |    0
       02  |  up     |  0,7083    |  145
       03  |  down   |  1,6102    |  330
       04  |  left   |  2,4683    |  505
       05  |  select |  3,6205    |  741
      --------------------------------------

Os valores da última coluna (Digital) são pertinentes à resolução ADC de 10 bits

 Tensão Máxima    = 5V
 Valor Máximo ADC = 1024

 Constante de Conversão = 1024/5 = 204,8

 Multiplicou-se os valores da coluna Tensão (V) pela constante de conversão
 e arredondou-se para o inteiro mais próximo, obtendo-se assim os limites
 de cada uma das 15 teclas.

*************************************************************************/
void keyboardRead()
{
     adc_value = analogRead(A0);                       //Variável para leitura recebe valor AD de A0

     // --- Testa se os botões foram pressionados ---
     // Se foi pressionado, seta a respectiva flag
     if      (adc_value <  50)                    butt01 = 0x01;
     else if (adc_value > 103 && adc_value < 200) butt02 = 0x01;
     else if (adc_value > 250 && adc_value < 380) butt03 = 0x01;
     else if (adc_value > 450 && adc_value < 550) butt04 = 0x01;
     
    

     // --- Testa se os botões foram liberados ---
     //
     if (adc_value > 50 && butt01)             //Botão right solto e flag butt01 setada?
     {                                         //Sim...
         butt01 = 0x00;                        //Limpa flag butt01
         right  = 0x01;                        //Seta flag right
         
     } //end right
     if (adc_value > 200 && butt02)            //Botão up solto e flag butt02 setada?
     {                                         //Sim...
         butt02 = 0x00;                        //Limpa flag butt02
         up     = 0x01;                        //Seta flag up
      
     } //end up
     if (adc_value > 380 && butt03)            //Botão down solto e flag butt03 setada?
     {                                         //Sim...
         butt03 = 0x00;                        //Limpa flag butt03
         down   = 0x01;                        //Seta flag down
       
     } //end down
     if (adc_value > 550 && butt04)            //Botão left solto e flag butt04 setada?
     {                                         //Sim...
         butt04 = 0x00;                        //Limpa flag butt04
         left   = 0x01;                        //Seta flag left
       
     } //end left
     


} //end keyboardRead

 



