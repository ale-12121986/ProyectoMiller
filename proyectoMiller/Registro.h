//#include "HardwareSerial.h"
#include "WString.h"
//Maestro
#include "Arduino.h"
#include <Wire.h>
class Registro{
  private:
  int registroLateral = 0, registroCircunferencial = 0, registroTintero = 0;
  int cuerpo = 0;
  char d = 0;
  byte nDato = 0;
  char cadena[20];  
  char message[4]; 

  char combinedMessage[10]; // Buffer para la cadena combinada
  public:
    //Configurar cuerpos
  void Configurar(){
    Wire.begin(); // join I2C bus (address optional for master)
        
  }
  void setEnviarDato(int dato){

  }

  void moverRegistroLateral(int valor){
    Wire.beginTransmission(2); // transmit to devi 
    strcpy(message, "lat");
    snprintf(combinedMessage, sizeof(combinedMessage), "%s%d", message, valor);
    Wire.write(combinedMessage);
    Wire.endTransmission();    // stop transmitting            
  }
  void moverRegistroCircunferencial(int valor){ // envio valor circunferencial
    Wire.beginTransmission(2); // transmit to devi
    strcpy(message, "cir");
    snprintf(combinedMessage, sizeof(combinedMessage), "%s%d", message, valor);
    Wire.write(combinedMessage);
    Wire.endTransmission();
  }

  String leerTransmisor(){
    //Serial.println("Entro en la recepcion de datos");
    Wire.requestFrom(2, 1);    // request 6 bytes from slave device #2
    nDato = 0;
    while (Wire.available()) {
      //Serial.println("----------------------------------------------------------------");
      d = Wire.read();
      //Serial.println(int(d));
    }
    //Serial.println("----------------------------------------------------------------");
    Wire.requestFrom(2,int(d));         
    strcpy(cadena, "");
    String cadenas= "";
    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      cadena[nDato] = c;
      cadenas =cadenas + c; 
      //Serial.print(cadena[nDato]); 
      nDato++;       
      }
      //Serial.println(cadenas);
      //Serial.println(" ");    
      return cadenas;
  }

  void activarCuerpos(int cuerpos){
    Serial.print("valor del cuerpo");
    Serial.println(cuerpos);
    cuerpo = cuerpos;
    Wire.beginTransmission(2); // transmit to devi 
    strcpy(message, "Cue");
    snprintf(combinedMessage, sizeof(combinedMessage), "%s%d", message, cuerpos);
    Wire.write(combinedMessage);
    Wire.endTransmission();    // stop transmitting
            
  }
  void DireccionBarra(int direccion){
    Wire.beginTransmission(2); // transmit to devi
    strcpy(message, "bgf");
    snprintf(combinedMessage, sizeof(combinedMessage), "%s%d", message, direccion);
    Wire.write(combinedMessage);        
    Wire.endTransmission();
    }
  void ValorBarra(int valor){
    Wire.beginTransmission(2); // transmit to devi
    strcpy(message, "gbv");
    snprintf(combinedMessage, sizeof(combinedMessage), "%s%d", message, valor);
    Wire.write(combinedMessage);        
    Wire.endTransmission();
  }
  void BarridoTinta(int valor){
    Wire.beginTransmission(2); // transmit to devi
    strcpy(message, "bbt");
    snprintf(combinedMessage, sizeof(combinedMessage), "%s%d", message, valor);
    Wire.write(combinedMessage);        
    Wire.endTransmission();
  }
};