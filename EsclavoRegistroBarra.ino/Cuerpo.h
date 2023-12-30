#include "HardwareSerial.h"
#include "Arduino.h"
class Cuerpo{
  private:
  const byte cuerpo1 = 2;   //Pin para activar el Rele cel cuerpo 1
  const byte cuerpo2 = 4;   //Pin para activar el Rele cel cuerpo 2
  const byte cuerpo3 = 5;   //Pin para activar el Rele cel cuerpo 3
  const byte cuerpo4 = 3;   //Pin para activar el Rele cel cuerpo 4
  const byte cuerpo5 = 9;   //Pin para activar el Rele cel cuerpo 5
  const byte cuerpo6 = 8;   //Pin para activar el Rele cel cuerpo 6
  int cuerpoSelec;
  public:
  void configurar(){
    pinMode(cuerpo1,OUTPUT);
    pinMode(cuerpo2,OUTPUT);
    pinMode(cuerpo3,OUTPUT);
    pinMode(cuerpo4,OUTPUT);
    pinMode(cuerpo5,OUTPUT);
    pinMode(cuerpo6,OUTPUT);
  }
  void seleccionarCuerpo(int cuerpo){
    cuerpoSelec = cuerpo;
    switch (cuerpo) {
      case 0: //condicion inical
        digitalWrite(cuerpo1, LOW);
        digitalWrite(cuerpo2, LOW);
        digitalWrite(cuerpo3, LOW);
        digitalWrite(cuerpo4, LOW);
        digitalWrite(cuerpo5, LOW);
        digitalWrite(cuerpo6, LOW);
        break;            
      case 1: //Se activo el cuerpo 1
        Serial.println("entro cuerpo 1");
        digitalWrite(cuerpo1, HIGH);
        digitalWrite(cuerpo2, LOW);
        digitalWrite(cuerpo3, LOW);
        digitalWrite(cuerpo4, LOW);
        digitalWrite(cuerpo5, LOW);
        digitalWrite(cuerpo6, LOW);
      break;
      case 2: //Se activo el cuerpo 2
        Serial.println("entro cuerpo 2");
        digitalWrite(cuerpo1, LOW);
        digitalWrite(cuerpo2, HIGH);
        digitalWrite(cuerpo3, LOW);
        digitalWrite(cuerpo4, LOW);
        digitalWrite(cuerpo5, LOW);
        digitalWrite(cuerpo6, LOW);
      break;
      case 3: //Se activo el cuerpo 3
        Serial.println("entro cuerpo 3");
        digitalWrite(cuerpo1, LOW);
        digitalWrite(cuerpo2, LOW);
        digitalWrite(cuerpo3, HIGH);
        digitalWrite(cuerpo4, LOW);
        digitalWrite(cuerpo5, LOW);
        digitalWrite(cuerpo6, LOW);
      break;
      case 4: //Se activo el cuerpo 4
        Serial.println("entro cuerpo 4");
        digitalWrite(cuerpo1, LOW);
        digitalWrite(cuerpo2, LOW);
        digitalWrite(cuerpo3, LOW);
        digitalWrite(cuerpo4, HIGH);
        digitalWrite(cuerpo5, LOW);
        digitalWrite(cuerpo6, LOW);
      break;
      case 5: //Se activo el cuerpo 5
        Serial.println("entro cuerpo 5");
        digitalWrite(cuerpo1, LOW);
        digitalWrite(cuerpo2, LOW);
        digitalWrite(cuerpo3, LOW);
        digitalWrite(cuerpo4, LOW);
        digitalWrite(cuerpo5, HIGH);
        digitalWrite(cuerpo6, LOW);
      break;
        case 6: //Se activo el cuerpo 6
        Serial.println("entro cuerpo 6");
        digitalWrite(cuerpo1, LOW);
        digitalWrite(cuerpo2, LOW);
        digitalWrite(cuerpo3, LOW);
        digitalWrite(cuerpo4, LOW);
        digitalWrite(cuerpo5, LOW);
        digitalWrite(cuerpo6, HIGH);
      break;
      default:
      break;
    }
  }
  int cuerpo(){
    return cuerpoSelec; 
  }
};