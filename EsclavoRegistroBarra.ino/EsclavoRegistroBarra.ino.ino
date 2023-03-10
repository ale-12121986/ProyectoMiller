#include "Cuerpo.h"
#include "RegistroCircunferencial.h"
#include "RegistroLateral.h"
#include <Wire.h>
#include "WString.h"
byte nDato = 0;
char cadena[4];
String prueba; 
char leerTransmisorCircunferencial[] = "TransmisorC";
char leerTransmisorLateral[] = "TransmisorL"; 
char dato = 0;
int cuerpo, contador = 0;
int valorTransmisor;
bool bandera = false ;
String variable2  = "";
bool acRegCir = false, acRegLat = false;
Cuerpo claseCuerpo;
RegistroCircunferencial registroCircunferencial;
RegistroLateral registroLateral;
void requestEvent() {
  contador++;
  if (contador == 2) {
    Wire.print(variable2);
    contador = 0;      
  }
  if (contador == 1) {
    if (acRegCir == true) {
      valorTransmisor = registroCircunferencial.leerPotenciometro(claseCuerpo.cuerpo());
    }
    if (acRegLat == true) {
      valorTransmisor = registroLateral.leerPotenciometro(claseCuerpo.cuerpo());
    }    
    int valor = valorTransmisor;
    variable2 = String(valor);
    Serial.println(valorTransmisor);  
    Wire.write(int(variable2.length())); // respond with message of 6 bytes para que funcione tiene q enviar un dato int con la guncion write
    Serial.println(variable2.length());
  }  

  // as expected by master
  //Serial.println("Dato enviado");
  }
void recibeDato(int howMany){
  Serial.println("entro en sub rutina");
  nDato = 0;
  strcpy(dato, "");
  strcpy(cadena, "");
  while (1 < Wire.available()) {
    dato = Wire.read();
    //Serial.print(dato);
    cadena[nDato] = dato;
    nDato++;
    if(strcmp(cadena,"Cue") == 0){        
      prueba = "CUERPO";
    } 
    if(strcmp(cadena,"cir") == 0){
      prueba = "REGC";
    }
    if(strcmp(cadena,"lat") == 0){
      prueba = "REGL";
    }
  }
  //strcpy(cadena, "");
  //cuerpo = int(cadena[nDato-1]);
  cuerpo = Wire.read();
  Serial.println(cadena);
  Serial.println(cuerpo); 
  bandera = true;
}
void setup() {
  // put your setup code here, to run once:
  claseCuerpo.configurar();
  registroCircunferencial.configurar();
  registroLateral.configurar();
  Serial.begin(115200);
  Wire.begin(2);
  Wire.onReceive(recibeDato);
  Wire.onRequest(requestEvent); // register event
  claseCuerpo.seleccionarCuerpo(0);
  Serial.println("Esclavo");
  registroCircunferencial.moverRegistro(0);
  registroLateral.moverRegistro(0);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if (bandera) {
    if (prueba.equals("CUERPO")) {
      Serial.println("entro en cambios de cuerpos");
      delay(5);
      bandera = false;
      claseCuerpo.seleccionarCuerpo(cuerpo);
    }
    if (prueba.equals("REGC")) {
      Serial.println("entro en registro circunferencial"); 
      acRegCir = true;
      acRegLat = false;
      bandera = false;
      registroCircunferencial.cuerpo(cuerpo);
      registroCircunferencial.moverRegistro(cuerpo);
    }
    if (prueba.equals("REGL")) {
      Serial.println("entro en registro lateral");
      acRegCir = false;      
      acRegLat = true;
      bandera = false;
      //registroLateral
      registroLateral.cuerpo(cuerpo);
      registroLateral.moverRegistro(cuerpo);
    }
    prueba = "";
  }  
}
