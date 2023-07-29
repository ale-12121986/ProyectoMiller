#include "HardwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"

class ControlClavija{
  private:
                     // placa interface 
  const byte a = A7; //8
  const byte b = A11;//4
  const byte c = A9; //6
  const byte d = A8; //7
  const byte e = A12;//3
  const byte f = A13;//2
  const byte g = A10;//5
  const byte h = A14;//1
  const byte i = A5; //10
  const byte j = A3; //12
  const byte k = A6; //9
  const byte l = A4; //11
  int direccion;
  int selecMotor;                      // Direccionde las clavijas 
  int N = 7;                           //1,2,3,4,5,6,7 
  int dirclavijas[7] ={e,f,b,g,c,d,a}; //e,f,a,g,c,d,b
  const int clavijas[6][15][7] = {
//             0               1               2               3               4               5               6               7               8               9              10              11              12              13              14
//         1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7 
/*1 0*/  {{1,1,1,1,0,1,1},{1,0,1,1,0,1,1},{0,1,1,1,0,1,1},{0,0,1,1,0,1,1},{1,1,0,1,0,1,1},{1,0,0,1,0,1,1},{0,1,0,1,0,1,1},{0,0,0,1,0,1,1},{1,1,1,0,0,1,1},{1,0,1,0,0,1,1},{0,1,1,0,0,1,1},{0,0,1,0,0,1,1},{1,1,0,0,0,1,1},{1,0,0,0,0,1,1},{0,1,0,0,0,1,1}},
/*2 1*/  {{1,1,1,1,1,0,1},{1,0,1,1,1,0,1},{0,1,1,1,1,0,1},{0,0,1,1,1,0,1},{1,1,0,1,1,0,1},{1,0,0,1,1,0,1},{0,1,0,1,1,0,1},{0,0,0,1,1,0,1},{1,1,1,0,1,0,1},{1,0,1,0,1,0,1},{0,1,1,0,1,0,1},{0,0,1,0,1,0,1},{1,1,0,0,1,0,1},{1,0,0,0,1,0,1},{0,1,0,0,1,0,1}},
/*3 2*/  {{1,1,1,1,0,0,1},{1,0,1,1,0,0,1},{0,1,1,1,0,0,1},{0,0,1,1,0,0,1},{1,1,0,1,0,0,1},{1,0,0,1,0,0,1},{0,1,0,1,0,0,1},{0,0,0,1,0,0,1},{1,1,1,0,0,0,1},{1,0,1,0,0,0,1},{0,1,1,0,0,0,1},{0,0,1,0,0,0,1},{1,1,0,0,0,0,1},{1,0,0,0,0,0,1},{0,1,0,0,0,0,1}},
/*4 3*/  {{1,1,1,1,1,1,0},{1,0,1,1,1,1,0},{0,1,1,1,1,1,0},{0,0,1,1,1,1,0},{1,1,0,1,1,1,0},{1,0,0,1,1,1,0},{0,1,0,1,1,1,0},{0,0,0,1,1,1,0},{1,1,1,0,1,1,0},{1,0,1,0,1,1,0},{0,1,1,0,1,1,0},{0,0,1,0,1,1,0},{1,1,0,0,1,1,0},{1,0,0,0,1,1,0},{0,1,0,0,1,1,0}},
/*5 4*/  {{1,1,1,1,0,1,0},{1,0,1,1,0,1,0},{0,1,1,1,0,1,0},{0,0,1,1,0,1,0},{1,1,0,1,0,1,0},{1,0,0,1,0,1,0},{0,1,0,1,0,1,0},{0,0,0,1,0,1,0},{1,1,1,0,0,1,0},{1,0,1,0,0,1,0},{0,1,1,0,0,1,0},{0,0,1,0,0,1,0},{1,1,0,0,0,1,0},{1,0,0,0,0,1,0},{0,1,0,0,0,1,0}},
/*6 5*/  {{1,1,1,1,1,0,0},{1,0,1,1,1,0,0},{0,1,1,1,1,0,0},{0,0,1,1,1,0,0},{1,1,0,1,1,0,0},{1,0,0,1,1,0,0},{0,1,0,1,1,0,0},{0,0,0,1,1,0,0},{1,1,1,0,1,0,0},{1,0,1,0,1,0,0},{0,1,1,0,1,0,0},{0,0,1,0,1,0,0},{1,1,0,0,1,0,0},{1,0,0,0,1,0,0},{0,1,0,0,1,0,0}},
};
  void imprimirDirClavija(int cuerpo, int placa){
    Serial.print("cuerpo: ");
    Serial.println(cuerpo);
    Serial.print("placa: ");
    Serial.println(placa); 
    Serial.println(" ");    
    for (int i=0; i<N; i++){
      digitalWrite(dirclavijas[i], clavijas[cuerpo-1][placa][i]);
      Serial.print(clavijas[cuerpo-1][placa][i]);     
    }
    delay(1);
  }
  public:

  void configurar(){
    pinMode(i, OUTPUT);
    pinMode(k, OUTPUT);
    pinMode(j, OUTPUT);
    pinMode(l, OUTPUT);
    pinMode(h, OUTPUT);
    //DDRK = B11111111;
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);  
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
  }

  void posInicial(){
    digitalWrite(j, LOW);//HIGH
  }
  
  void motorIzquierdoMas(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(h, LOW);// HIGH
    digitalWrite(j, HIGH);//LOW
    digitalWrite(i, LOW);//HIGH
    digitalWrite(k, HIGH);//LOW
    digitalWrite(l, LOW);//HIGH
    delay(25);
    digitalWrite(l, HIGH);//LOW  
  }
  void motorIzquierdoMenos(int cuerpo, int placa){    
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(h, LOW);//HIGH
    digitalWrite(j, HIGH);//LOW
    digitalWrite(i, HIGH);//LOW
    digitalWrite(k, LOW);//HIGH
    digitalWrite(l, LOW);//HIGH
    delay(25);
    digitalWrite(l, HIGH);//LOW
  }
  void motorDerechoMas(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(j, HIGH);//LOW
    digitalWrite(h, HIGH);//LOW
    digitalWrite(i, LOW);//HIGH
    digitalWrite(k, HIGH);//LOW
    digitalWrite(l, LOW);//HIGH
    delay(25);
    digitalWrite(l, HIGH);//LOW  
  }
  void motorDerechoMenos(int cuerpo ,int placa){
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(j, HIGH);//LOW
    digitalWrite(h, HIGH);//LOW
    digitalWrite(i, HIGH);//LOW
    digitalWrite(k, LOW);//HIGH
    digitalWrite(l, LOW);//HIGH
    delay(25);
    digitalWrite(l, HIGH);//LOW
  }

  void resetflipflop(){
    digitalWrite(i, HIGH);//LOW
    digitalWrite(k, HIGH);//LOW
    digitalWrite(l, LOW);//HIGH
    delay(5);
    digitalWrite(l, HIGH);//LOW
    digitalWrite(j, LOW);//HIGH
    for (int i=0; i<N; i++){
      digitalWrite(dirclavijas[i], HIGH);//LOW       
    }
  }
  
  void leerPotIzquierdo(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    delay(10); 
    digitalWrite(h, HIGH);//LOW
    digitalWrite(j, LOW);//HIGH
    
  }
  void leerPotderecho(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    delay(10); 
    digitalWrite(h, LOW);//HIGH
    digitalWrite(j, LOW);//HIGH
    
  }
};