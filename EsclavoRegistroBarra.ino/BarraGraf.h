#include "Arduino.h"
class BarraGraf{
  private:
    boolean habRegistroBajo = true, habRegistroAlto = true, habilitador = true;  
    const byte dato1 = 22;
    const byte dato2 = 23;
    const byte dato3 = 24;
    const byte dato4 = 25;
    const byte dato5 = 26;
    const byte dato6 = 27;
    const byte dato7 = 28;
    const byte dato8 = 29;
    const byte dato9 = 30;
    const byte dato10 = 31;
    const byte dato11 = 32;
    const byte dato12 = 33;
    const byte dato13 = 34;
    const byte dato14 = 35;
    const byte dato15 = 36;
    const byte dato16 = 37;
    const byte dir1 = 38;
    const byte dir2 = 39;
    const byte dir3 = 40;
    const byte dir4 = 41;
    const byte dir5 = 42;
    const byte dir6 = 43;
    const byte clock1 = 44;
    const byte clock2 = 45;
    const byte clock3 = 46;
    byte datos[16] = {dato1, dato2, dato3, dato4, dato5, dato6, dato7, dato8,dato9, dato10, dato11, dato12, dato13, dato14, dato15, dato16};
    byte direccion[6] = {dir1, dir2, dir3, dir4,dir5, dir6};
    byte clocks[3] ={clock1, clock2, clock3};
    byte direcciones[29][6] ={
      /* 1*/ {0,0,0,0,0,0},
      /* 1*/ {1,0,0,0,0,0},
      /* 2*/ {0,1,0,0,0,0},
      /* 3*/ {1,1,0,0,0,0},
      /* 4*/ {0,0,1,0,0,0},
      /* 5*/ {1,0,1,0,0,0},
      /* 6*/ {0,1,1,0,0,0},
      /* 7*/ {1,1,1,0,0,0},
      /* 8*/ {0,0,0,1,0,0}, 
      /* 9*/ {1,0,0,1,0,0},
      /*10*/ {0,1,0,1,0,0},
      /*11*/ {1,1,0,1,0,0},
      /*12*/ {0,0,1,1,0,0},
      /*13*/ {1,0,1,1,0,0},
      /*14*/ {0,1,1,1,0,0},
      /*15*/ {1,1,1,1,0,0},
      /*16*/ {0,0,0,0,1,0},
      /*17*/ {1,0,0,0,1,0},
      /*18*/ {0,1,0,0,1,0}, 
      /*19*/ {1,1,0,0,1,0},
      /*20*/ {0,0,1,0,1,0},
      /*21*/ {1,0,1,0,1,0},
      /*22*/ {0,1,1,0,1,0},
      /*23*/ {1,1,1,0,1,0},
      /*24*/ {0,0,0,1,1,0},
      /*25*/ {1,0,0,1,1,0},
      /*26*/ {0,1,0,1,1,0},
      /*27*/ {1,1,0,1,1,0}, 
      /*28*/ {0,0,1,1,1,0},      
    };
    byte valortintero[17][16] ={
      /* 0*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      /* 1*/ {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      /* 2*/ {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      /* 3*/ {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
      /* 4*/ {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
      /* 5*/ {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
      /* 6*/ {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
      /* 7*/ {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
      /* 8*/ {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0}, 
      /* 9*/ {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
      /*10*/ {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
      /*11*/ {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
      /*12*/ {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
      /*13*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
      /*14*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
      /*15*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
      /*16*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };        
  public: 

  void configurar(){
    for (int i = 0; i<16; i++){
      pinMode(datos[i], OUTPUT);
      digitalWrite(datos[i], LOW);
    }      
    for (int i = 0; i<6; i++){    
      pinMode(direccion[i], OUTPUT);
      digitalWrite(direccion[i], LOW);
    }
    for (int i = 0; i<4; i++){    
      pinMode(clocks[i], OUTPUT);
      digitalWrite(clocks[i], LOW);
    }    
  }
  
  void direccionar(byte valor){
    for (int i = 0; i < 6; i++){
        digitalWrite(direcciones[i], direcciones[valor][i]);
        digitalWrite(clocks[3], HIGH);
      }
  }
    
  void imprimir(int valor){
    if(valor < 51){
      digitalWrite(clocks[0], HIGH);
      for (int i = 0; i < 18; i++) {
        digitalWrite(datos[i], valortintero[valor][i]);
      }            
      digitalWrite(clocks[0], LOW);
    }
    else if(valor > 51 && valor < 100){
      valor = valor - 50;
      digitalWrite(clocks[1], HIGH);
      for (int i = 0; i < 18; i++) {
        digitalWrite(datos[i], valortintero[valor][i]);
      }            
      digitalWrite(clocks[1], LOW);
    }
      digitalWrite(clocks[2], LOW);
  }
  
};