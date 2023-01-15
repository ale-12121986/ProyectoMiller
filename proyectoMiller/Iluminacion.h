#include "Arduino.h"
class Iluminacion{
  private:
  //direccion de la iluminacion   
    const byte luz2 = 37;     //cuerpo1
    const byte luz3 = 38;     //cuerpo3
    const byte luz4 = 39;     // Barrido tinta centro
    const byte luz5 = 40;     //cuerpo4
    const byte luz6 = 41;     //M1   
    const byte luz7 = 42;     //M2
    const byte luz8 = 43;     //Error
    const byte luz11 = 44;   //cuerpo6
    const byte luz12 = 45;   //cuerpo5
    const byte luz16 = 46;   //cuerpo2
    int dirControlIluminacion[10] = {
      luz2, luz3, luz4, luz5, luz6, luz7, luz8, luz11,
      luz12, luz16
    };
  
  public:
  void configurar(){
    for(int i=0; i<=15;i++){
      pinMode(dirControlIluminacion[i], OUTPUT);
      digitalWrite(dirControlIluminacion[i], LOW);
    }         
  }
  void encenderCuerpo(int cuerpoActivado){
    switch (cuerpoActivado) {
      case 0:      
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
      break;
      case 1: // enciede luz cuerpo 1
        digitalWrite(luz2, LOW);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;    
      case 2: // enciede luz cuerpo 2
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, LOW);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;
      case 3: // enciede luz cuerpo 3
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, LOW);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;
      case 4: // enciede luz cuerpo 4
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, LOW);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;              
      case 5: // enciede luz cuerpo 5
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, LOW);
        digitalWrite(luz11, HIGH);  
        break;
      case 6: // enciede luz cuerpo 6
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, LOW);  
        break;    
      default:
          break;
    }
  }
  void trabajoMemoria(int valor){
    switch (valor) {
    case 0:
      digitalWrite(luz7, HIGH);
      digitalWrite(luz8, HIGH);
      digitalWrite(luz4, HIGH);        
      digitalWrite(luz6, HIGH);
    case 1:   //Se seleccion M1    
      digitalWrite(luz7, HIGH);
      digitalWrite(luz8, HIGH);
      digitalWrite(luz4, HIGH);        
      digitalWrite(luz6, LOW);
      break;
    case 2:
      digitalWrite(luz6, HIGH);
      digitalWrite(luz8, HIGH);
      digitalWrite(luz4, HIGH);        
      digitalWrite(luz7, LOW);
      break;
    default:
    break;    
    }
  }
};