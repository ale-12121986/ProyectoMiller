
#include "HardwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"

class RegistroCircunferencial{
  private:
  const byte registro1 = A1;    //potenciometro de registro circunferencial del cuerpo 1
  const byte datoA = A3;
  const byte datoB = A5;
  const byte datoC = A7;
  // const byte registro2 = A3;    //potenciometro de registro circunferencial del cuerpo 2
  // const byte registro3 = A5;    //potenciometro de registro circunferencial del cuerpo 3
  // const byte registro4 = A7;    //potenciometro de registro circunferencial del cuerpo 4
  // const byte registro5 = A9;    //potenciometro de registro circunferencial del cuerpo 5
  // const byte registro6 = A11;   //potenciometro de registro circunferencial del cuerpo 6
  const byte rCirMas = 12; //8
  const byte rCirMenos = 13; //9
  int cuerpos = 1;
  int dato;

  
  public:
  void configurar(){
    pinMode(registro1, INPUT);
    pinMode(datoA, OUTPUT);
    pinMode(datoB, OUTPUT);
    pinMode(datoC, OUTPUT);

    pinMode(rCirMas, OUTPUT);
    pinMode(rCirMenos, OUTPUT);
  }

  void moverRegistro(int valor){
    //Serial.print("entro a mover registro ");
    //Serial.print(valor);
    switch (valor) {   
    case 1:   //centrar registro
      centrarRegistro();
    break;
    case 2:   //subir registro
      //Serial.println("subir");
      digitalWrite(rCirMas, HIGH);
      digitalWrite(rCirMenos, LOW);
    break;
    case 3:   //bajar registro
      //Serial.println("bajar");
      digitalWrite(rCirMas, LOW);
      digitalWrite(rCirMenos, HIGH);
    break;
    case 4:   //descativar
      //Serial.println("parar");
      digitalWrite(rCirMas, LOW);
      digitalWrite(rCirMenos, LOW);
    break;
    default:
    break;
    }    
  }  
  int leerPotenciometro(int cuerpo){
    //Serial.print("Entro en leer Pot ");
    //Serial.println(cuerpo);
    if (cuerpo == 1) {
      digitalWrite(datoA, HIGH);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(registro1);
      //regCirCuerpo1 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);
      if (dato<= 200 || dato >= 900) {
      moverRegistro(4);
      }
      return dato;
    }
    else if (cuerpo == 2) {
      digitalWrite(datoA, LOW);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(registro1);
      //regCirCuerpo2 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);
      if (dato<= 200 || dato >= 900) {
      moverRegistro(4);
      }       
      return dato;
    }
    else if (cuerpo == 3) {
      digitalWrite(datoA, HIGH);
      digitalWrite(datoB, LOW);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(registro1);
      //regCirCuerpo3 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);
      if (dato<= 200 || dato >= 900) {
      moverRegistro(4);
      }       
      return dato;
    }
    else if (cuerpo == 4) {
      digitalWrite(datoA, LOW);
      digitalWrite(datoB, LOW);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(registro1);
      //int regCirCuerpo4 = map(dato, 0, 1023, -90, 90);
      //Serial.println(dato);
      if (dato<= 200 || dato >= 900) {
      moverRegistro(4);
      }
      return dato;
    }
    else if (cuerpo == 5) {
      digitalWrite(datoA, HIGH);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, LOW);
      delay(1);
      dato = analogRead(registro1);
      //int regCirCuerpo5 = map(dato, 0, 1023, -90, 90);
      //Serial.println(dato);
      if (dato<= 200 || dato >= 900) {
      moverRegistro(4);
      }        
      return dato;
    }
    else if (cuerpo == 6) {
      digitalWrite(datoA, LOW);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, LOW);
      delay(1);
      dato = analogRead(registro1);
      //Serial.println(dato);
      if (dato<= 200 || dato >= 900) {
      moverRegistro(4);
      }       
      return dato;
    }
  }
  void cuerpo(int cuerpo){
    cuerpos = cuerpo;   
  }
  void centrarRegistro(){
    //Serial.println("entro en centrar");        
    bool centrar =false;
    int dato = 0;
    while (centrar == false) {
      dato = leerPotenciometro(cuerpos);
      if(dato <= 490){
        digitalWrite(rCirMas, HIGH);
        digitalWrite(rCirMenos, LOW);
      }
      if(dato >= 520){
        digitalWrite(rCirMas, LOW);
        digitalWrite(rCirMenos, HIGH);
      }
      if((dato >= 491) && (dato <= 519)){
        centrar = true;
      }
    }
  }
};