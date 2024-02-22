#include "Arduino.h"
class Iluminacion{
  private:
  //direccion de la iluminacion   
    const byte luzxx = 6;
    const byte luz2 = 5;     //cuerpo1
    const byte luz3 = 48;     //cuerpo3
    const byte luz4 = 2;     // Barrido tinta centro
    const byte luz5 = 47;     //cuerpo4
    const byte luz6 = 51;     //M1   
    const byte luz7 = 50;     //M2
    const byte luz8 = 49;     //Error
    const byte luz11 = 45;   //cuerpo6
    const byte luz12 = 46;   //cuerpo5
    const byte luz16 = 52;   //cuerpo2
    const byte luz17 = 3;    //cambio de cuerpo ojo falta programar
    const byte luz18 = 4;    //guardar en memoria ojo falta programar 
    int dirControlIluminacion[13] = {
      luz2, luz3, luz4, luz5, luz6, luz7, luz8, luz11,
      luz12, luz16 ,luz17 ,luz18, luzxx
    };
  
  public:
  void configurar(){
    for(int i=0; i<=12;i++){
      pinMode(dirControlIluminacion[i], OUTPUT);
      digitalWrite(dirControlIluminacion[i], HIGH);
    }         
  }
  void encenderCuerpo(int cuerpoActivado){
    switch (cuerpoActivado) {
      case 0:
        digitalWrite(luzxx, HIGH);      
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        //digitalWrite(luz7, HIGH);
        digitalWrite(luz11, HIGH); 
        digitalWrite(luz17, HIGH);
        digitalWrite(luz18, HIGH); 

      break;
      case 1: // enciede luz cuerpo 1
        digitalWrite(luzxx, LOW);
        digitalWrite(luz2, LOW);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;    
      case 2: // enciede luz cuerpo 2
        digitalWrite(luzxx, HIGH);
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, LOW);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;
      case 3: // enciede luz cuerpo 3
        digitalWrite(luzxx, HIGH);
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, LOW);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;
      case 4: // enciede luz cuerpo 4
        digitalWrite(luzxx, HIGH);
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, LOW);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);  
        break;              
      case 5: // enciede luz cuerpo 5
        digitalWrite(luzxx, HIGH);
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, LOW);
        digitalWrite(luz11, HIGH);  
        break;
      case 6: // enciede luz cuerpo 6
        digitalWrite(luzxx, HIGH);
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, LOW);  
        break;    
         case 7: // enciede luz cambio de cuerpo
        digitalWrite(luzxx, HIGH);
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);
        digitalWrite(luz17, LOW);
        digitalWrite(luz18, HIGH);  
        break;    
        case 8: // enciede luz guardar en memoria
        digitalWrite(luzxx, HIGH);
        digitalWrite(luz2, HIGH);
        digitalWrite(luz16, HIGH);
        digitalWrite(luz3, HIGH);        
        digitalWrite(luz5, HIGH);
        digitalWrite(luz12, HIGH);
        digitalWrite(luz11, HIGH);
        digitalWrite(luz17, HIGH);
        digitalWrite(luz18, LOW);  
        break;
        case 9: // enciede luz guardar en memoria
        //digitalWrite(luz18, HIGH);  
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
      break;
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