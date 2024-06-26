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
  String registroDeLectura = "";  
  
  public:
    //Configurar cuerpos
  void Configurar(){
    Wire.begin(); // join I2C bus (address optional for master)
        
  }
  void setEnviarDato(int dato){

  }

  void moverRegistroLateral(int valor){
    Wire.beginTransmission(2); // transmit to devi 
    Wire.write("lat");
    registroDeLectura = "lateral";
    delay(1);
    Wire.write(valor);
    Wire.endTransmission();    // stop transmitting            
  }
  void moverRegistroCircunferencial(int valor){ // envio valor circunferencial
    Wire.beginTransmission(2); // transmit to devi
    Wire.write("cir");
    registroDeLectura = "circunferencial";
    delay(1);
    Wire.write(valor);
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
    Wire.write("Cue");
    delay(2);
    Wire.write(cuerpos);              // sends one byte
    Wire.endTransmission();    // stop transmitting
            
  }
  void DireccionBarra(int direccion){
      Wire.beginTransmission(2); // transmit to devi        
      Wire.write("bgf");   
      delay(2);
      Wire.write(direccion);              // sends one byte
      delay(2);
      Wire.endTransmission();
    }
  void ValorBarra(int valor){
    Wire.beginTransmission(2); // transmit to devi        
      Wire.write("bgv");   
      delay(2);
      Wire.write(valor);              // sends one byte
      delay(2);
      Wire.endTransmission();
  }
  void BarridoTinta(int valor){
    Wire.beginTransmission(2); // transmit to devi        
      Wire.write("bbt");   
      delay(2);
      Wire.write(valor);              // sends one byte
      delay(2);
      Wire.endTransmission();
  }
};