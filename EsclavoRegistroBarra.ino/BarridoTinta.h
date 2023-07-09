#include "Arduino.h"
class BarridoTinta{
  private:

  const byte barridoMas = 12;
  const byte barridoMenos = 13;
  
  public:
  void configurar(){
    pinMode(barridoMas, OUTPUT);
    pinMode(barridoMenos, OUTPUT);
  }

  void moverRegistro(int valor){
    Serial.print("entro a mover barrido tinta ");
    Serial.print(valor);
    switch (valor) {   
    case 1:   //centrar registro
      centrarRegistro();
    break;
    case 2:   //subir registro
      Serial.println("subir");
      digitalWrite(barridoMas, LOW);
      digitalWrite(barridoMenos, HIGH);
    break;
    case 3:   //bajar registro
      Serial.println("bajar");
      digitalWrite(barridoMas, HIGH);
      digitalWrite(barridoMenos, LOW);
    break;
    case 4:   //descativar
      Serial.println("parar");
      digitalWrite(barridoMas, HIGH);
      digitalWrite(barridoMenos, HIGH);
    break;
    default:
    break;
    }    
  }
  void centrarRegistro(){

  }
};