#include "Arduino.h"
#include "EEPROM.h"
#include "ControlClavija.h"

class GrabadoMemoria{
  private:
ControlClavija controlarClavija;  
  const int pot = A0;
  int valor = 0;
  int valorPot = 0, valorMemoria = 0, dirMemoria = 0;
  int8_t dirMemoria = 0;
  //const int motores[6][28] ={
/*      1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28 */    
/*1*///{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27},
/*2*///{ 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55},
/*3*///{ 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 59, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83},
/*4*///{ 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111},
/*5*///{112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139},
/*6*///{140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167},
//  };

  public:
  void guardarMemoria(int cuerpos){   //Se guarda en memoria el valor de todos los potenciometros de cada cuerpo  
    //ControlClavija controlarClavija;
    for (int i= 1; i<= 14; i++){
      controlarClavija.leerPotIzquierdo(cuerpos, i);
      retardo100ms(); 
      valor = analogRead(pot);
      EEPROM.put(dirMemoria, valor1);
      dirMemoria++;
      controlarClavija.leerPotderecho(cuerpos, i);
      retardo100ms(); 
      valor = analogRead(pot);
      EEPROM.put(dirMemoria, valor);
      dirMemoria++;
    }
  }
  
  void compararValoresCuerpos(int cuerpos){
    for(int i = 1; i<=14; i++){
      EEPROM.get(dirMemoria, valorMemoria);
      controlarClavija.leerPotIzquierdo(cuerpos, i);
      retardo100ms(); 
      valorPot = analogRead(pot);
      while (valorPot < valorMemoria) {
      controlarClavija.motorIzquierdoMas(cuerpos, i);
      }  
      while(valorPot > valorMemoria) {
        controlarClavija.motorIzquierdoMenos(cuerpos, i);
      }
      dirMemoria++;
      EEPROM.get(dirMemoria, valorMemoria);
      controlarClavija.leerPotderecho(cuerpos, i);
      retardo100ms();
      valorPot =analogRead(pot);
      while (valorPot < valorMemoria) {
      controlarClavija.motorDerechoMas(cuerpos, i);
      }  
      while(valorPot > valorMemoria) {
        controlarClavija.motorDerechoMenos(cuerpos, i);
      }             
      dirMemoria++;    
    }      
  }
} ;