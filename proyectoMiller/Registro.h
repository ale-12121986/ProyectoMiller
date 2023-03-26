#include "HardwareSerial.h"
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
    Wire.write("lateral");
    registroDeLectura = "lateral";
    switch (valor) {
    case 1: //centra el valor lateral
      Wire.write("LC");
      Wire.endTransmission();    // stop transmitting
    break;
    case 2: //incrementa el valor lateral
      Wire.write("LI");
      Wire.endTransmission();    // stop transmitting
    break;
    case 3: //disminuye el valor lateral
      Wire.write("LD");
      Wire.endTransmission();    // stop transmitting
    break;
    default:
    break;
    }          
  }
  void moverRegistroCircunferencial(int valor){
    Wire.beginTransmission(2); // transmit to devi
    Wire.write("circunferencial");
    registroDeLectura = "circunferencial";
    switch (valor) {
    case 1: //centra el valor lateral
      Wire.write("CC");
      Wire.endTransmission();    // stop transmitting
    break;
    case 2: //incrementa el valor lateral
      Wire.write("CI");
      Wire.endTransmission();    // stop transmitting
    break;
    case 3: //disminuye el valor lateral
      Wire.write("CD");
      Wire.endTransmission();    // stop transmitting
    break;
    default:
    break;
    }
  }
  void  leerTransmisor(){
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
    Serial.print(cadena[nDato]); 
    nDato++;       
    }
    Serial.println(cadenas);
    Serial.println(" ");
}
  void activarCuerpos(int cuerpos){
    //Serial.print("envia por i2c");
    cuerpo = cuerpos;
    Wire.beginTransmission(2); // transmit to devi        
    Wire.write("CUE");
    //Wire.endTransmission();
    switch (cuerpos) {
    case 1:
      //Wire.beginTransmission(2); // transmit to devi 
      Wire.write(cuerpos);              // sends one byte
      Wire.endTransmission();    // stop transmitting
    break;
    case 2:
      //Wire.beginTransmission(2); // transmit to devi 
      Wire.write(cuerpos);              // sends one byte
      Wire.endTransmission();    // stop transmitting    
    break;
    case 3:
    //Wire.beginTransmission(2); // transmit to devi 
      Wire.write(cuerpos);              // sends one byte
      Wire.endTransmission();    // stop transmitting    
    break;
    case 4:
    //Wire.beginTransmission(2); // transmit to devi 
      Wire.write(cuerpos);              // sends one byte
      Wire.endTransmission();    // stop transmitting    
    break;
    case 5:
    //Wire.beginTransmission(2); // transmit to devi 
      Wire.write(cuerpos);              // sends one byte
      Wire.endTransmission();    // stop transmitting    
    break;
    case 6:
    //Wire.beginTransmission(2); // transmit to devi 
      Wire.write(cuerpos);              // sends one byte
      Wire.endTransmission();    // stop transmitting    
    break;
    default:
    break;   
    }        
  }
};