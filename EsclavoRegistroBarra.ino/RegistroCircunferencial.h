
#include "HardwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"

class RegistroCircunferencial{
  private:
  byte registro1 = A1;    //potenciometro de registro circunferencial del cuerpo 1
  byte registro2 = A3;    //potenciometro de registro circunferencial del cuerpo 2
  byte registro3 = A5;    //potenciometro de registro circunferencial del cuerpo 3
  byte registro4 = A7;    //potenciometro de registro circunferencial del cuerpo 4
  byte registro5 = A9;    //potenciometro de registro circunferencial del cuerpo 5
  byte registro6 = A11;   //potenciometro de registro circunferencial del cuerpo 6
  byte registroCircunferencialMas = 8;
  byte registroCircunferencialMenos = 9;
  int cuerpos = 1;
  int dato;

  
  public:
  void configurar(){
    pinMode(registro1, INPUT);
    pinMode(registro2, INPUT);
    pinMode(registro3, INPUT);
    pinMode(registro4, INPUT);
    pinMode(registro5, INPUT);
    pinMode(registro6, INPUT);
    pinMode(registroCircunferencialMas, OUTPUT);
    pinMode(registroCircunferencialMenos, OUTPUT);
  }

  void moverRegistro(int valor){
    switch (valor) {
    case 0:   //descativar
      digitalWrite(registroCircunferencialMas, HIGH);
      digitalWrite(registroCircunferencialMenos, HIGH);
    break;
    case 1:   //centrar registro
      centrarRegistro();
    break;
    case 2:   //subir registro
      Serial.println("subir");
      digitalWrite(registroCircunferencialMas, LOW);
      digitalWrite(registroCircunferencialMenos, HIGH);
    break;
    case 3:   //bajar registro
      Serial.println("bajar");
      digitalWrite(registroCircunferencialMas, HIGH);
      digitalWrite(registroCircunferencialMenos, LOW);
    break;
    default:
    break;
    }    
  }  
  int leerPotenciometro(int cuerpo){
    //Serial.print("Entro en leer Pot ");
    //Serial.println(cuerpo);
    if (cuerpo == 1) {
      dato = analogRead(registro1);
      //regCirCuerpo1 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);        
      return dato;
    }
    else if (cuerpo == 2) {
      dato = analogRead(registro2);
      //regCirCuerpo2 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);        
      return dato;
    }
    else if (cuerpo == 3) {
      dato = analogRead(registro3);
      //regCirCuerpo3 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);        
      return dato;
    }
    else if (cuerpo == 4) {
      dato = analogRead(registro4);
      //regCirCuerpo4 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);
                   
      return dato;
    }
    else if (cuerpo == 5) {
      dato = analogRead(registro5);
      //regCirCuerpo5 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);        
      return dato;
    }
    else if (cuerpo == 6) {
      dato = analogRead(registro6);
      //regCirCuerpo6 = map(dato, 0, 1023, 0, 512);
      //Serial.println(dato);        
      return dato;
    }
  }
  void cuerpo(int cuerpo){
    cuerpos = cuerpo;   
  }
  void centrarRegistro(){
    Serial.println("entro en centrar");        
    bool centrar =false;
    int dato = 0;
    while (centrar == false) {
      dato = leerPotenciometro(cuerpos);
      if(dato <= 490){
        digitalWrite(registroCircunferencialMas, HIGH);
        digitalWrite(registroCircunferencialMenos, LOW);
      }
      if(dato >= 520){
        digitalWrite(registroCircunferencialMas, LOW);
        digitalWrite(registroCircunferencialMenos, HIGH);
      }
      if((dato >= 491) && (dato <= 519)){
        centrar = true;
      }
    }
  }
};