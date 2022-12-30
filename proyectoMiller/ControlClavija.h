#include "HardwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"

class ControlClavija{
  private:
  
  const byte i = A7;//a7
  const byte k = A6;//a6
  const byte j = A5;//a5
  const byte l = A4;//a4
  const byte h = A3;//a3
  const byte a = A8;
  const byte b = A9;
  const byte c = A10;
  const byte d = A11;
  const byte e = A12;
  const byte f = A13;
  const byte g = A14;
  int direccion;
  int selecMotor;                      // Direccionde las clavijas 
  int N = 7;                           //1,2,3,4,5,6,7 
  int dirclavijas[7] ={e,f,b,g,c,d,a}; //e,f,a,g,c,d,b
  const int clavijas[6][15][7] = {
//             0               1               2               3               4               5               6               7               8               9              10              11              12              13              14
//       1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7   1 2 3 4 5 6 7 
/*1 0*/  {{0,0,0,0,1,0,0},{0,1,0,0,1,0,0},{1,0,0,0,1,0,0},{1,1,0,0,1,0,0},{0,0,1,0,1,0,0},{0,1,1,0,1,0,0},{1,0,1,0,1,0,0},{1,1,1,0,1,0,0},{0,0,0,1,1,0,0},{0,1,0,1,1,0,0},{1,0,0,1,1,0,0},{1,1,0,1,1,0,0},{0,0,1,1,1,0,0},{0,1,1,1,1,0,0},{1,0,1,1,1,0,0}},
/*2 1*/  {{0,0,0,0,0,1,0},{0,1,0,0,0,1,0},{1,0,0,0,0,1,0},{1,1,0,0,0,1,0},{0,0,1,0,0,1,0},{0,1,1,0,0,1,0},{1,0,1,0,0,1,0},{1,1,1,0,0,1,0},{0,0,0,1,0,1,0},{0,1,0,1,0,1,0},{1,0,0,1,0,1,0},{1,1,0,1,0,1,0},{0,0,1,1,0,1,0},{0,1,1,1,0,1,0},{1,0,1,1,0,1,0}},
/*3 2*/  {{0,0,0,0,1,1,0},{0,1,0,0,1,1,0},{1,0,0,0,1,1,0},{1,1,0,0,1,1,0},{0,0,1,0,1,1,0},{0,1,1,0,1,1,0},{1,0,1,0,1,1,0},{1,1,1,0,1,1,0},{0,0,0,1,1,1,0},{0,1,0,1,1,1,0},{1,0,0,1,1,1,0},{1,1,0,1,1,1,0},{0,0,1,1,1,1,0},{0,1,1,1,1,1,0},{1,0,1,1,1,1,0}},
/*4 3*/  {{0,0,0,0,0,0,1},{0,1,0,0,0,0,1},{1,0,0,0,0,0,1},{1,1,0,0,0,0,1},{0,0,1,0,0,0,1},{0,1,1,0,0,0,1},{1,0,1,0,0,0,1},{1,1,1,0,0,0,1},{0,0,0,1,0,0,1},{0,1,0,1,0,0,1},{1,0,0,1,0,0,1},{1,1,0,1,0,0,1},{0,0,1,1,0,0,1},{0,1,1,1,0,0,1},{1,0,1,1,0,0,1}},
/*5 4*/  {{0,0,0,0,1,0,1},{0,1,0,0,1,0,1},{1,0,0,0,1,0,1},{1,1,0,0,1,0,1},{0,0,1,0,1,0,1},{0,1,1,0,1,0,1},{1,0,1,0,1,0,1},{1,1,1,0,1,0,1},{0,0,0,1,1,0,1},{0,1,0,1,1,0,1},{1,0,0,1,1,0,1},{1,1,0,1,1,0,1},{0,0,1,1,1,0,1},{0,1,1,1,1,0,1},{1,0,1,1,1,0,1}},
/*6 5*/  {{0,0,0,0,0,1,1},{0,1,0,0,0,1,1},{1,0,0,0,0,1,1},{1,1,0,0,0,1,1},{0,0,1,0,0,1,1},{0,1,1,0,0,1,1},{1,0,1,0,0,1,1},{1,1,1,0,0,1,1},{0,0,0,1,0,1,1},{0,1,0,1,0,1,1},{1,0,0,1,0,1,1},{1,1,0,1,0,1,1},{0,0,1,1,0,1,1},{0,1,1,1,0,1,1},{1,0,1,1,0,1,1}},
};
  void imprimirDirClavija(int cuerpo, int placa){
    Serial.print("cuerpo: ");
    Serial.println(cuerpo);
    Serial.print("placa: ");
    Serial.println(placa); 
    Serial.println(" ");    
    for (int i=0; i<N; i++){
      digitalWrite(dirclavijas[i], clavijas[cuerpo-1][placa][i]);
      Serial.println(clavijas[cuerpo-1][placa][i]);     
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
    digitalWrite(j, HIGH);
  }
  
  void motorIzquierdoMas(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(h, HIGH);
    digitalWrite(j, LOW);
    digitalWrite(i, HIGH);
    digitalWrite(k, LOW);
    digitalWrite(l, HIGH);
    delay(25);
    digitalWrite(l, LOW);
    
    
  }
  void motorIzquierdoMenos(int cuerpo, int placa){    
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(h, HIGH);
    digitalWrite(j, LOW);
   
    digitalWrite(i, LOW);
    digitalWrite(k, HIGH);
    digitalWrite(l, HIGH);
    delay(25);
    digitalWrite(l, LOW);
    
    
  }
  void motorDerechoMas(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(j, LOW);
    digitalWrite(h, LOW);
    digitalWrite(i, HIGH);
    digitalWrite(k, LOW);
    digitalWrite(l, HIGH);
    delay(25);
    digitalWrite(l, LOW);
    
    
  }
  void motorDerechoMenos(int cuerpo ,int placa){
    imprimirDirClavija(cuerpo, placa);
    digitalWrite(j, LOW);
    digitalWrite(h, LOW);
    digitalWrite(i, LOW);
    digitalWrite(k, HIGH);
    digitalWrite(l, HIGH);
    delay(25);
    digitalWrite(l, LOW);
    
    
  }
  void resetflipflop(){
    digitalWrite(i, LOW);
    digitalWrite(k, LOW);
    digitalWrite(l, HIGH);
    delay(5);
    digitalWrite(l, LOW);
    digitalWrite(j, HIGH);
    for (int i=0; i<N; i++){
      digitalWrite(dirclavijas[i], LOW);       
    }
  }
  
  void leerPotIzquierdo(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    delay(5); 
    digitalWrite(h, LOW);
    digitalWrite(j, HIGH);
    
  }
  void leerPotderecho(int cuerpo, int placa){
    imprimirDirClavija(cuerpo, placa);
    delay(5); 
    digitalWrite(h, HIGH);
    digitalWrite(j, HIGH);
    
  }
};