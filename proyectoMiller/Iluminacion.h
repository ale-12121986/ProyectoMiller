#include "Arduino.h"
class Iluminacion{
  private:
  //direccion de la iluminacion
    const byte luz1 = 37;   
    const byte luz2 = 38;    //cuerpo1
    const byte luz3 = 39;    
    const byte luz4 = 40;    //cuerpo3
    const byte luz5 = 41;    //cuerpo4
    const byte luz6 = 42;    
    const byte luz7 = 43;
    const byte luz8 = 44;
    const byte luz9 = 45;
    const byte luz10 = 46;
    const byte luz11 = 47;   //cuerpo6
    const byte luz12 = 48;   //cuerpo5
    const byte luz13 = 49;
    const byte luz14 = 50;
    const byte luz15 = 51;
    const byte luz16 = 52;   //cuerpo2
    int dirControl[16] = {
      luz1, luz2, luz3, luz4, luz5, luz6, luz7, luz8, luz9, luz10, luz11,
      luz12, luz13,luz14, luz15, luz16
    };
  
  public:
  void configurar(){
    for(int i=0; i<=15;i++){
      pinMode(dirControl[i], OUTPUT);
      digitalWrite(dirControl[i], LOW);
    }         
  }
  void encenderCuerpo(int cuerpoActivado){
    switch (cuerpoActivado) {
      case 1: // enciede luz cuerpo 1
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, LOW);
        digitalWrite(luz4, LOW);        
        digitalWrite(luz5, LOW);
        digitalWrite(luz12, LOW);
        digitalWrite(luz11, LOW);  
        break;    
      case 2: // enciede luz cuerpo 2
        digitalWrite(luz2, LOW);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz4, LOW);        
        digitalWrite(luz5, LOW);
        digitalWrite(luz12, LOW);
        digitalWrite(luz11, LOW);  
        break;
      case 3: // enciede luz cuerpo 3
        digitalWrite(luz2, LOW);
        digitalWrite(luz16, LOW);
        digitalWrite(luz4, HIGH);        
        digitalWrite(luz5, LOW);
        digitalWrite(luz12, LOW);
        digitalWrite(luz11, LOW);  
        break;
      case 4: // enciede luz cuerpo 4
        digitalWrite(luz2, LOW);
        digitalWrite(luz16, LOW);
        digitalWrite(luz4, LOW);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, LOW);
        digitalWrite(luz11, LOW);  
        break;              
      case 5: // enciede luz cuerpo 5
        digitalWrite(luz2, LOW);
        digitalWrite(luz16, LOW);
        digitalWrite(luz4, LOW);        
        digitalWrite(luz5, LOW);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, LOW);  
        break;
      case 6: // enciede luz cuerpo 6
        digitalWrite(luz2, LOW);
        digitalWrite(luz16, LOW);
        digitalWrite(luz4, LOW);        
        digitalWrite(luz5, LOW);
        digitalWrite(luz12, LOW);
        digitalWrite(luz11, HIGH);  
        break;    
      default:
          break;      
    }
  }  
};