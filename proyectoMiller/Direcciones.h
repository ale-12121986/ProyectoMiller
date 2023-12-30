#include "Arduino.h"
class Direcciones{
  private:
  int dir[4];
  const int dirComandos[16][4] = {
    /*0*/ {0,0,0,0},  //LK0
    /*1*/ {1,0,0,0},  //LK1
    /*2*/ {0,1,0,0},  //LK2  registro circunferencial
    /*3*/ {1,1,0,0},  //LK3  registro lateral
    /*4*/ {0,0,1,0},  //LK4  Seleccionar cuerpos
    /*5*/ {1,0,1,0},  //LK5  Fuente de tinta
    /*6*/ {0,1,1,0},  //LK6  Trabajo/Memoria
    /*7*/ {1,1,1,0},  //LK7
    /*8*/ {0,0,0,1},  //LK8  Cuerpos de tinteros
    /*9*/ {1,0,0,1},  //LK9  Cuerpos de tinteros
    /*10*/{0,1,0,1}, //LK10  Cuerpos de tinteros
    /*11*/{1,1,0,1}, //LK11  Cuerpos de tinteros
    /*12*/{0,0,1,1}, //LK12  Cuerpos de tinteros
    /*13*/{1,0,1,1}, //LK13  Cuerpos de tinteros
    /*14*/{0,1,1,1}, //LK14  Cuerpos de tinteros
    /*15*/{1,1,1,1}  //LK15  Cuerpos de tinteros
  };
  
  // Direcciones de las placas de control
  const byte Dir0 = 31; //direccion 1  30
  const byte Dir1 = 30; //direccion 2  32
  const byte Dir2 = 33; //direccion 3  32
  const byte Dir3 = 32; //direccion 4  33
  int N = 4;
  int dirControl[4] = { Dir0, Dir1, Dir2, Dir3};
    public:
    void configurar(){
      for (int i=0; i<N; i++){
      pinMode(dirControl[i], OUTPUT);
      }
    }
    void imprimirDireccion(int placas){
      for (int i=0; i<N; i++){
        digitalWrite(dirControl[i], dirComandos[placas][i] );
        //Serial.print(dirComandos[placas][i]);
        dir[i] = dirComandos[placas][i];
      }
    }
    void imprimirLaDireccion(){
      //Serial.print("direccion de placa: ");
      for (int i=0; i<N; i++){
        //Serial.print(dir[i]);
      }
      //Serial.println("");
    }

};