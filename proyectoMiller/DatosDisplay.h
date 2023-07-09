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
    const byte u1 = 37;   //D0.0
    const byte u2 = 40;   //D0.1
    const byte u3 = 39;   //D0.2
    const byte u4 = 38;   //D0.3
    const byte d1 = 44;   //D0
    const byte d2 = 42;   //D1
    const byte d3 = 41;   //D2
    const byte d4 = 43;   //D3
    const byte dis1 = 34;
    const byte dis2 = 35;
    const byte habilitarDisplay = 36; 
    int N = 4;
    int displayUnidad[4] = {u1, u2, u3, u4};
    int displayDecena[4] = {d1, d2, d3, d4};
    void selecDisplay(int pines){ // configura los pines para seleccionar que display se va a escribir
      switch (pines) {
        case 1:
          //Serial.println("display 1");  // Escribe el display 1
          digitalWrite(dis1, LOW);
          digitalWrite(dis2, LOW);
          break;
        case 2:
          //Serial.println("display 2");  // Escribe el display 2
          digitalWrite(dis1, HIGH);
          digitalWrite(dis2, LOW);
          break;
        case 3:
          //Serial.println("display 3");  // Escribe el display 3
          digitalWrite(dis1, LOW);
          digitalWrite(dis2, HIGH);
          break;
        case 4:
          //Serial.println("display 4");  // Escribe el display 4
          digitalWrite(dis1, HIGH);
          digitalWrite(dis2, HIGH);
        break;
        default:
          break;
      }
    }
    void imprimirDisplay(int unidad, int decena){
      Serial.print("valor: ");
      int yy =decena*10 +unidad;
      Serial.println(yy);
      for (int i=0; i<4; i++){
        digitalWrite(displayUnidad[i], DIGITOS[unidad][i]);
        digitalWrite(displayDecena[i], DIGITOS[decena][i]);
        //Serial.print(DIGITOS[decena][i]);
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
    delay(5);
    imprimirDisplay(unidad, decena);
    delay(1);
    digitalWrite(habilitarDisplay, HIGH);
    delay(1);
    digitalWrite(habilitarDisplay, LOW);
  }
    void enviarDatoRegistro(int unidad, int decena, int centena, int negativo){    
    selecDisplay(1);
    imprimirDisplay(centena, negativo);
    delay(1);
    digitalWrite(habilitarDisplay, HIGH);
    delay(10);
    digitalWrite(habilitarDisplay, LOW);
    delay(10);
    selecDisplay(2);
    imprimirDisplay(unidad,decena);
    delay(1);
    digitalWrite(habilitarDisplay, HIGH);
    delay(10);
    digitalWrite(habilitarDisplay, LOW);
  }  

};