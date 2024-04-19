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
    const byte habilitarclock = 44;
    const byte enviarDatoBajo = 46;
    const byte enviarDatoAlto = 45;
    int datos[16] = {dato1, dato2, dato3, dato4, dato5, dato6, dato7, dato8, dato9, dato10, dato11, dato12, dato13, dato14, dato15, dato16};
    int direccionPuerto[6] = {dir1, dir2, dir3, dir4, dir5, dir6};
    //int clocks[3] ={clock0, clock1, clock2};
    const int datoDirecciones[29][6] ={
      /* 0*/ {1,1,1,1,1,1},
      /* 1*/ {0,1,1,1,1,1},
      /* 2*/ {1,0,1,1,1,1},
      /* 3*/ {0,0,1,1,1,1},
      /* 4*/ {1,1,0,1,1,1},
      /* 5*/ {0,1,0,1,1,1},
      /* 6*/ {1,0,0,1,1,1},
      /* 7*/ {0,0,0,1,1,1},
      /* 8*/ {1,1,1,0,1,1}, 
      /* 9*/ {0,1,1,0,1,1},
      /*10*/ {1,0,1,0,1,1},
      /*11*/ {0,0,1,0,1,1},
      /*12*/ {1,1,0,0,1,1},
      /*13*/ {0,1,0,0,1,1},
      /*14*/ {1,0,0,0,1,1},
      /*15*/ {0,0,0,0,1,1},
      /*16*/ {1,1,1,1,0,1},
      /*17*/ {0,1,1,1,0,1},
      /*18*/ {1,0,1,1,0,1}, 
      /*19*/ {0,0,1,1,0,1},
      /*20*/ {1,1,0,1,0,1},
      /*21*/ {0,1,0,1,0,1},
      /*22*/ {1,0,0,1,0,1},
      /*23*/ {0,0,0,1,0,1},
      /*24*/ {1,1,1,0,0,1},
      /*25*/ {0,1,1,0,0,1},
      /*26*/ {1,0,1,0,0,1},
      /*27*/ {0,0,1,0,0,1}, 
      /*28*/ {1,1,0,0,0,1},      
    };
    const int valortintero[17][16] ={
      /* 0*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      /* 1*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
      /* 2*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
      /* 3*/ {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
      /* 4*/ {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
      /* 5*/ {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
      /* 6*/ {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
      /* 7*/ {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
      /* 8*/ {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0}, 
      /* 9*/ {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
      /*10*/ {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
      /*11*/ {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
      /*12*/ {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
      /*13*/ {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
      /*14*/ {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      /*15*/ {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      /*16*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
  int y = 0;
  public: 

  void configurar(){
    for (int i = 0; i<16; i++){
      pinMode(datos[i], OUTPUT);
      digitalWrite(datos[i], LOW);
    }      
    for (int i = 0; i<6; i++){    
      pinMode(direccionPuerto[i], OUTPUT);
      digitalWrite(direccionPuerto[i], HIGH);
    }
    pinMode(habilitarclock, OUTPUT);
    pinMode(enviarDatoBajo, OUTPUT);
    pinMode(enviarDatoAlto, OUTPUT);
    digitalWrite(habilitarclock, LOW);
    digitalWrite(enviarDatoAlto, LOW);
    digitalWrite(enviarDatoBajo, LOW);
  }
  
  void direccionar(byte valor){
    digitalWrite(habilitarclock, LOW); //deshabilitador de clock
    Serial.println(valor);
    for (int i = 0; i < 6; i++){
        digitalWrite(direccionPuerto[i], datoDirecciones[valor][i]);
        //Serial.print(datoDirecciones[valor][i]);
      }
  }
    
  void imprimir(int valor){
    if(valor <= 50){
      y = map(valor, 0, 50, 0, 16);
      //Serial.print("entro el primer grupo de leds y encendio: ");
      //Serial.println(y);    
      for (int i = 0; i<16; i++) {
        digitalWrite(datos[i], valortintero[y][i]);
        //Serial.print(valortintero[y][i]);
        if(y<=16){
          habilitarDatoBajo();
        }
        else{
          digitalWrite(enviarDatoBajo, LOW);
        }
      }
    }
    //prueba
    if(valor > 50 ){
      //Serial.print("entro el segundo grupo de leds y encendio: ");
      valor = valor - 50;
      y = map(valor, 0, 50, 0, 16);
      Serial.println(y);
      for (int i = 0; i < 16; i++) {
        digitalWrite(datos[i], valortintero[y][i]);
        //Serial.print(valortintero[y][i]);
        if(y<=16){
          habilitarDatoAlto();
        }
        else{
          digitalWrite(enviarDatoAlto, LOW);
        }
      }
    }
  }
  void habilitarDatoAlto(){
    digitalWrite(habilitador, LOW);  //habilito el clock
    digitalWrite(enviarDatoAlto, HIGH);  //dejar de escribir los segundos 16 bits
    digitalWrite(enviarDatoBajo, LOW);  //escribir los primeros 16 bits
  }
  void habilitarDatoBajo(){
    digitalWrite(habilitador, LOW);  //habilito el clock  
    digitalWrite(enviarDatoBajo, HIGH);
    digitalWrite(enviarDatoAlto, LOW);
  }
};