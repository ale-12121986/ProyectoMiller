#include "pins_arduino.h"
#include "Arduino.h"
class BarridoTinta{
  private:

  const byte barridoMas = 7;
  const byte barridoMenos = 6; //13
  
  public:
  void configurar(){
    pinMode(barridoMas, OUTPUT);
    pinMode(barridoMenos, OUTPUT);
  }

  void moverRegistro(int valor){
    //Serial.print("entro a mover barrido tinta ");
    //Serial.print(valor);
    switch (valor) {   
    case 1:   //centrar registro
      centrarRegistro();
    break;
    case 2:   //subir registro
      //Serial.println("subir +");
      digitalWrite(barridoMas, HIGH);
      digitalWrite(barridoMenos, LOW);
    break;
    case 3:   //bajar registro
      //Serial.println("bajar -");
      digitalWrite(barridoMas, LOW);
      digitalWrite(barridoMenos, HIGH);
    break;
    case 4:   //descativar
      //Serial.println("parar");
      digitalWrite(barridoMas, LOW);
      digitalWrite(barridoMenos, LOW);
    break;
    default:
    break;
    }    
  }
  void centrarRegistro(){

  }
};