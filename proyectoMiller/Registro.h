#include "Arduino.h"
class Registro{
  private:
  //Datos de cuerpo y registro
    const bool regLat1 = 10;
    const bool regLat2 = 11;
    const bool regCir1 = 12;
    const bool regCir2 = 13;
    const bool regInc1 = 14;
    const bool regInc2 = 15;
    const bool concartorCuerpo1 = 47;
    const bool concartorCuerpo2 = 48;
    const bool concartorCuerpo3 = 49;
    const bool concartorCuerpo4 = 50; 
    const bool concartorCuerpo5 = 51;
    const bool concartorCuerpo6 = 52;
    int dirControl[10] = {
      regLat1, regLat2, regCir1, regCir2, regInc1, concartorCuerpo1, concartorCuerpo2, concartorCuerpo3,
      concartorCuerpo4, concartorCuerpo5, concartorCuerpo6
    };
  public:
    //Configurar cuerpos
  void configurar(){
    
  }

};