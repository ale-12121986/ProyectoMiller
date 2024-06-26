#include "Cuerpo.h"
#include "RegistroCircunferencial.h"
#include "RegistroLateral.h"
#include "BarraGraf.h"
#include "BarridoTinta.h"
#include <Wire.h>
#include "WString.h"
byte nDato = 0;
char cadena[4];
String prueba; 
char leerTransmisorCircunferencial[] = "TransmisorC";
char leerTransmisorLateral[] = "TransmisorL"; 
char dato;
int cuerpo, contador = 0;
int valorTransmisor;
bool bandera = false ;
String variable2  = "";
bool acRegCir = false, acRegLat = false, acBar= false;
Cuerpo claseCuerpo;
RegistroCircunferencial registroCircunferencial;
RegistroLateral registroLateral;
BarraGraf barraGRaf;
BarridoTinta barridoTinta;
void requestEvent() {
  contador++;
  if (contador == 2) {
    Wire.print(variable2);
    contador = 0;      
  }
  if (contador == 1) {
    if (acRegCir == true) { //entro a leer los valores del registro circunferencial
      valorTransmisor = registroCircunferencial.leerPotenciometro(claseCuerpo.cuerpo());
      //Serial.println("envio el dato circunferencial");
    }
    if (acRegLat == true) { //entro a leer los valores del registro lateral
      valorTransmisor = registroLateral.leerPotenciometro(claseCuerpo.cuerpo());
      //Serial.println("envio el dato lateral");
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
  //Serial.println("entro en sub rutina");
  nDato = 0;
  //strcpy(dato, "");
  //strcpy(cadena, "");
  while (1 < Wire.available()) {
    dato = Wire.read();
    //Serial.print(dato);
    cadena[nDato] = dato;
    nDato++;
    if(strcmp(cadena,"Cue") == 0){ 
      Serial.print("entro a cuerpo");       
      prueba = "CUER";
    } 
    if(strcmp(cadena,"cir") == 0){
      prueba = "REGC";
    }
    if(strcmp(cadena,"lat") == 0){
      prueba = "REGL";
    }
    if(strcmp(cadena,"bgf") == 0){
      prueba = "BGF";
    }
    if(strcmp(cadena,"bgv") == 0){
      prueba = "BGV";
    }
    if(strcmp(cadena,"bbt") == 0){
      prueba = "BBT";
    }
  }
  strcpy(cadena, "");
  //cuerpo = int(cadena[nDato-1]);
  cuerpo = Wire.read();
  //Serial.println(cadena);
  //Serial.println(cuerpo); 
  bandera = true;
}
void setup() {
  // put your setup code here, to run once:
  claseCuerpo.configurar();
  registroCircunferencial.configurar();
  registroLateral.configurar();
  barraGRaf.configurar();
  Serial.begin(115200);
  Wire.begin(2);
  Wire.onReceive(recibeDato);
  Wire.onRequest(requestEvent); // register event
  claseCuerpo.seleccionarCuerpo(0);
  Serial.println( "Esclavo esclavo");
  registroCircunferencial.moverRegistro(4);
  registroLateral.moverRegistro(0);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if (bandera) {
    if (prueba.equals("CUER")) {
      Serial.println("entro en cambios de cuerpos"+ cuerpo);
      delay(10);
      bandera = false;
      claseCuerpo.seleccionarCuerpo(cuerpo);
      delay(10);
      claseCuerpo.seleccionarCuerpo(cuerpo);
    }
    if (prueba.equals("REGC")) {
      //Serial.println("entro en registro circunferencial"); 
      acRegCir = true;  //leer valores del registro circunferencial activado
      acRegLat = false; //leer valores del registro lateral desactivado
      bandera = false;
      //registroCircunferencial.cuerpo(cuerpo);
      registroCircunferencial.moverRegistro(cuerpo);
    }
    if (prueba.equals("REGL")) {
      //Serial.println("entro en registro lateral");
      acRegCir = false;  //leer valores del registro circunferencial desactivado
      acRegLat = true;  //leer valores del registro circunferencial activado
      bandera = false;
      //registroLateral
      //registroLateral.cuerpo(cuerpo);
      registroLateral.moverRegistro(cuerpo);
    }
    if (prueba.equals("BGF")) {
 //     Serial.println("entro en la dir de barra ");
      //Serial.print(cuerpo);
      //barraGRaf.direccionar(cuerpo);
      
    }
    if(prueba.equals("BGV")){
      //Serial.println("entro en elcuerpo de barra");
      barraGRaf.imprimir(cuerpo);
    }    
    if(prueba.equals("BBT")){
   //   Serial.println("entro en elcuerpo de barrido tinta mutua");
      barridoTinta.moverRegistro(cuerpo);
    }
    prueba = "";
  }  
}
