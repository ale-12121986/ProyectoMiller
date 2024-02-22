#include "HardwareSerial.h"
#include "pins_arduino.h"
#include "Arduino.h"
class RegistroLateral{
  private:
  byte lateral1 = A0;   //potenciometro de registro lateral del cuerpo 1
  const byte datoA = A2;
  const byte datoB = A4;
  const byte datoC = A6;
  // byte lateral2 = A2;   //potenciometro de registro lateral del cuerpo 2
  // byte lateral3 = A4;   //potenciometro de registro lateral del cuerpo 3
  // byte lateral4 = A6;   //potenciometro de registro lateral del cuerpo 4
  // byte lateral5 = A8;   //potenciometro de registro lateral del cuerpo 5
  // byte lateral6 = A10;  //potenciometro de registro lateral del cuerpo 6
  byte registroLateralMas = 10;
  byte registroLateralMenos = 11;
  
  int dato, cuerpos = 1;
 
  public:
  void configurar(){
    pinMode(lateral1, INPUT);
    pinMode(datoA, OUTPUT);
    pinMode(datoB, OUTPUT);
    pinMode(datoC, OUTPUT);
    
    pinMode(registroLateralMas, OUTPUT);
    pinMode(registroLateralMenos, OUTPUT);
  }
  void moverRegistro(int valor){
    switch (valor) {
    case 0:   //descativar
      digitalWrite(registroLateralMas, LOW);
      digitalWrite(registroLateralMenos, LOW);
    break;
    case 1:   //centrar registro
    break;
    case 2:   //subir registro
      Serial.println("sube");
      digitalWrite(registroLateralMas, HIGH);
      digitalWrite(registroLateralMenos, LOW);
    break;
    case 3:   //bajar registro
      Serial.println("baja");
      digitalWrite(registroLateralMas, LOW);
      digitalWrite(registroLateralMenos, HIGH);
    break;
    default:
    break;
    }    
  }
  int leerPotenciometro(int cuerpo){
    Serial.println("Entro en leer Pot ");
    Serial.print(cuerpo);
    if (cuerpo == 1) {
      digitalWrite(datoA, HIGH);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(lateral1);
      Serial.println(dato);        
      return dato;
    }
    else if (cuerpo == 2) {
      digitalWrite(datoA, LOW);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(lateral1);
      Serial.println(dato);  
      return dato;
    }
    else if (cuerpo == 3) {
      digitalWrite(datoA, HIGH);
      digitalWrite(datoB, LOW);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(lateral1);
      Serial.println(dato);
      return dato;
    }
    else if (cuerpo == 4) {
      digitalWrite(datoA, LOW);
      digitalWrite(datoB, LOW);
      digitalWrite(datoC, HIGH);
      delay(1);
      dato = analogRead(lateral1);
      Serial.println(dato);
      return dato;
    }
    else if (cuerpo == 5) {
      digitalWrite(datoA, HIGH);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, LOW);
      delay(1);
      dato = analogRead(lateral1);
      Serial.println(dato); 
      return dato;
    }
    else if (cuerpo == 6) {
      Serial.println("Barra laterial cuerpo 6 multi");
      digitalWrite(datoA, LOW);
      digitalWrite(datoB, HIGH);
      digitalWrite(datoC, LOW);
      dato = analogRead(lateral1);
      //regLatCuerpo6 = map(dato, 0, 1023, -99, 99);
      Serial.println(dato);        
      return dato;
    }
  }
  void cuerpo(int cuerpo){
    cuerpos = cuerpo;   
  } 
  void centrarRegistro(){
  
    bool centrar =false;
    int dato = 0;
    while (centrar == false) {
      dato = leerPotenciometro(cuerpos);
      if(dato <= 490){
        digitalWrite(registroLateralMas, HIGH);
        digitalWrite(registroLateralMenos, LOW);
      }
      if(dato >= 520){
        digitalWrite(registroLateralMas, LOW);
        digitalWrite(registroLateralMenos, HIGH);
      }
      if((dato >= 491) && (dato <= 519)){
        centrar = true;
      }
    }    
  }
};