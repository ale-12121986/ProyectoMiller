#include "Arduino.h"
class Direcciones{
  private:
  const int dirComandos[16][4] = {
    /*0*/ {0,0,0,0},  //LK0
    /*1*/ {1,0,0,0},  //LK1
    /*2*/ {0,1,0,0},  //LK2
    /*3*/ {1,1,0,0},  //LK3
    /*4*/ {0,0,1,0},  //LK4
    /*5*/ {1,0,1,0},  //LK5
    /*6*/ {0,1,1,0},  //LK6 Trabajo/Memoria
    /*7*/ {1,1,1,0},  //LK7
    /*8*/ {0,0,0,1},  //LK8
    /*9*/ {1,0,0,1},  //LK9
    /*10*/{0,1,0,1}, //LK10
    /*11*/{1,1,0,1}, //LK11
    /*12*/{0,0,1,1}, //LK12
    /*13*/{1,0,1,1}, //LK13
    /*14*/{0,1,1,1}, //LK14
    /*15*/{1,1,1,1}  //LK15
  };
  // Direcciones de las placas de control
  const byte Dir0 = 33;//direccion 1
  const byte Dir1 = 34;//direccion 2
  const byte Dir2 = 35;//direccion 3
  const byte Dir3 = 36;//direccion 4
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
      }
    }
};