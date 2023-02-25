#include <Wire.h>
#include "WString.h"
const byte Boton2 = 2;
const byte Boton6 = 3;
const byte Boton7 = 4;
const byte Boton1 = 5;
const byte Boton5 = 6;
const byte Boton8 = 7;
const byte Boton4 = 8;
const byte Boton3 = 9;
char d = 0;
char datoRecibido[4];
int registroLateral = 0, registroCircunferencial = 0, registroTintero = 0;
byte nDato = 0;
char cadena[20];
String cadena2 = "";
int cuerpo = 0;
int valorTransmisor; 
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
  cadena2 ="";
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    cadena[nDato] = c;
    cadena2 = cadena2 + String(c);
    //Serial.print(cadena[nDato]);
    nDato++;       
    }  
    Serial.println(cadena2);    
    Serial.println(" ");
}
void moverRegistroLateral(int valor){
  Wire.beginTransmission(2); // transmit to devi 
  Wire.write("lat");    //lateral
  switch (valor) {
  case 0:   //desactiva el registro lateral
    Wire.write(0);
    Wire.endTransmission();    // stop transmitting  
  break;  
  case 1: //centra el valor lateral
    Wire.write(1);
    Wire.endTransmission();    // stop transmitting
  break;
  case 2: //incrementa el valor lateral
    Wire.write(2);
    Wire.endTransmission();    // stop transmitting
  break;
  case 3: //disminuye el valor lateral
    Wire.write(3);
    Wire.endTransmission();    // stop transmitting
  break;
  default:
  break;
  }          
}
void moverRegistroCircunferencial(int valor){
  Wire.beginTransmission(2); // transmit to devi
  Wire.write("cir"); //circunferencial
  switch (valor) {
    case 0: //desactiva registro circunferencial
    Wire.write(0); 
    Wire.endTransmission();    // stop transmitting
  break;    
  case 1: //centra el valor lateral  
    Wire.write(1);
    Wire.endTransmission();    // stop transmitting
  break;
  case 2: //incrementa el valor lateral
    Wire.write(2);
    Wire.endTransmission();    // stop transmitting
  break;
  case 3: //disminuye el valor lateral
    Wire.write(3);
    Wire.endTransmission();    // stop transmitting
  break;
  default:
  break;
  }
}
void activarCuerpos(int cuerpos){
  cuerpo = cuerpos;
  Wire.beginTransmission(2); // transmit to devi        
  Wire.write("CUERPO");  
  switch (cuerpos) {
  case 1:
    Wire.write(cuerpos);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  break;
  case 2:
    Wire.write(cuerpos);              // sends one byte
    Wire.endTransmission();    // stop transmitting    
  break;
  case 3:
    Wire.write(cuerpos);              // sends one byte
    Wire.endTransmission();    // stop transmitting    
  break;
  case 4:
    Wire.write(cuerpos);              // sends one byte
    Wire.endTransmission();    // stop transmitting    
  break;
  case 5:
    Wire.write(cuerpos);              // sends one byte
    Wire.endTransmission();    // stop transmitting    
  break;
  case 6:
    Wire.write(cuerpos);              // sends one byte
    Wire.endTransmission();    // stop transmitting    
  break;
  default:
  break;   
  }        
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // join I2C bus (address optional for master)
  Serial.begin(115200);
  pinMode(Boton1, INPUT);
  pinMode(Boton2, INPUT);
  pinMode(Boton3, INPUT);
  pinMode(Boton4, INPUT);
  pinMode(Boton5, INPUT);
  pinMode(Boton6, INPUT);
  pinMode(Boton7, INPUT);
  pinMode(Boton8, INPUT);
  Serial.println("Maestro");
}
void loop() {
  if(digitalRead(Boton1) == HIGH){
    while(digitalRead(Boton1) == HIGH){     
    } 
    cuerpo++;
    if (cuerpo == 7) {
    cuerpo = 1;
    }
    Serial.println("Se activan los cuerpos");
    Serial.print(cuerpo);
    activarCuerpos(cuerpo);    
  }
  if(digitalRead(Boton2) == HIGH){
    Serial.println("circunferencial mas");
    moverRegistroCircunferencial(2);
    while(digitalRead(Boton2) == HIGH){     
      leerTransmisor();
    }
    moverRegistroCircunferencial(0);        
  }
  
  if(digitalRead(Boton3) == HIGH){
    Serial.println("circunferencial menos");
    moverRegistroCircunferencial(3);
    delay(10);
    while(digitalRead(Boton3) == HIGH){ 
      leerTransmisor();  
    }
    moverRegistroCircunferencial(0);        
  }
  if(digitalRead(Boton4) == HIGH){
    Serial.println("lateral mas");
    moverRegistroLateral(2);
    while(digitalRead(Boton4) == HIGH){  
      leerTransmisor();      
    }
    moverRegistroLateral(0);        
  }
  if(digitalRead(Boton5) == HIGH){
    Serial.println("lateral menos");
    moverRegistroLateral(3);
    while(digitalRead(Boton5) == HIGH){     
      leerTransmisor();
    }
    moverRegistroLateral(0);        
  }
}
