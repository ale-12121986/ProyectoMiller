#include "HardwareSerial.h"
#include "Arduino.h"
class DatosDisplay{
  private:
    int datoUnidad=0;
    int datoDecena=0;
    int display=0;
    int clavija;
    const int DIGITOS[10][4] = {
/*0*/ {0,0,0,0},
/*1*/ {1,0,0,0},
/*2*/ {0,1,0,0},
/*3*/ {1,1,0,0},
/*4*/ {0,0,1,0},
/*5*/ {1,0,1,0},
/*6*/ {0,1,1,0},
/*7*/ {1,1,1,0},
/*8*/ {0,0,0,1},
/*9*/ {1,0,0,1},
};  
    const int u1 = 22;
    const int u2 = 24;
    const int u3 = 26;
    const int u4 = 28;
    const int d1 = 23;
    const int d2 = 25;
    const int d3 = 27;
    const int d4 = 29;
    const byte dis1 = 30;
    const byte dis2 = 31;
    const int habilitarDisplay = 32; 
    int N = 4;
    int displayUnidad[4] = {u1, u2, u3, u4};
    int displayDecena[4] = {d1, d2, d3, d4};
    void selecDisplay(int pines){ // configura los pines para seleccionar que display se va a escribir
      switch (pines) {
        case 1:
          Serial.println("display 1");  // Escribe el display 1
          digitalWrite(dis1, LOW);
          digitalWrite(dis2, LOW);
          break;
        case 2:
          Serial.println("display 2");  // Escribe el display 2
          digitalWrite(dis1, HIGH);
          digitalWrite(dis2, LOW);
          break;
        case 3:
          Serial.println("display 3");  // Escribe el display 3
          digitalWrite(dis1, LOW);
          digitalWrite(dis2, HIGH);
          break;
        case 4:
          Serial.println("display 4");  // Escribe el display 4
          digitalWrite(dis1, HIGH);
          digitalWrite(dis2, HIGH);
        break;
        default:
          break;
      }
    }
    void imprimirDisplay(int unidad, int decena){
      for (int i=0; i<N; i++){
        digitalWrite(displayUnidad[i], DIGITOS[unidad][i]);
        digitalWrite(displayDecena[i], DIGITOS[decena][i]);
      }
    }
  public:
  void configurar(){
    pinMode(habilitarDisplay, OUTPUT);
    pinMode(dis1, OUTPUT);
    pinMode(dis2, OUTPUT);
    //DDRA=B11111111;
    for (int i=0; i<N; i++){
      pinMode(displayUnidad[i], OUTPUT);
      pinMode(displayDecena[i], OUTPUT);
      digitalWrite(displayUnidad[i], LOW);//apagar
      digitalWrite(displayDecena[i], LOW);//apagar
    }
  }
  void enviarDato(int unidad, int decena, int pines){
    selecDisplay(pines);
    imprimirDisplay(unidad, decena);
    delay(1);
    digitalWrite(habilitarDisplay, HIGH);
    delay(10);
    digitalWrite(habilitarDisplay, LOW);
  }

};