#include "Cuerpo.h"
#include "RegistroCircunferencial.h"
#include "RegistroLateral.h"
#include "BarraGraf.h"
#include "BarridoTinta.h"
#include <Wire.h>
#include "WString.h"
byte nDato = 0;
char cadena[5];
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

  //Serial.println("Dato enviado");
}
void recibeDato(int howMany){
  //Serial.println("entro en sub rutina");
  nDato = 0;
  dato = '\0';  // Esto vacía el contenido de dato
  strcpy(cadena, "");
  while (Wire.available()) {
    dato = Wire.read();
    Serial.print(dato);
    cadena[nDato] = dato;
    nDato++;
    if(strcmp(cadena,"Cue1") == 0){ 
      prueba = "CUER1";
    }
    if(strcmp(cadena,"Cue2") == 0){ 
      prueba = "CUER2";
    }
    if(strcmp(cadena,"Cue3") == 0){ 
      prueba = "CUER3";
    }
    if(strcmp(cadena,"Cue4") == 0){ 
      prueba = "CUER4";
    }
    if(strcmp(cadena,"Cue5") == 0){ 
      prueba = "CUER5";
    }
    if(strcmp(cadena,"Cue6") == 0){ 
      
      prueba = "CUER6";
    } 
    if(strcmp(cadena,"cir1") == 0){
      prueba = "REGC1";
    }
    if(strcmp(cadena,"cir2") == 0){
      prueba = "REGC2";
    }
    if(strcmp(cadena,"cir3") == 0){
      prueba = "REGC3";
    }
    if(strcmp(cadena,"cir4") == 0){
      prueba = "REGC4";
    }
    if(strcmp(cadena,"lat1") == 0){
      prueba = "REGL1";
    }
    if(strcmp(cadena,"lat2") == 0){
      prueba = "REGL2";
    }
    if(strcmp(cadena,"lat3") == 0){
      prueba = "REGL3";
    }
    if(strcmp(cadena,"lat0") == 0){
      prueba = "REGL0";
    }
    if(strcmp(cadena,"bgf") == 0){
      prueba = "BGF";
    }
    if(strcmp(cadena,"bgv") == 0){
      prueba = "BGV";
    }
    if(strcmp(cadena,"bbt1") == 0){
      prueba = "BBT1";
    }
    if(strcmp(cadena,"bbt2") == 0){
      prueba = "BBT2";
    }
    if(strcmp(cadena,"bbt3") == 0){
      prueba = "BBT3";
    }
    if(strcmp(cadena,"bbt4") == 0){
      prueba = "BBT4";
    }
  }
  strcpy(cadena, "");
  bandera = true;
}
void setup() {
  // put your  setup code here, to run once:
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
    if (prueba.equals("CUER1")) {
      bandera = false;
      cuerpo = 1;
      claseCuerpo.seleccionarCuerpo(1);
      delay(10);

    }
    if (prueba.equals("CUER2")) {
      bandera = false;
      cuerpo = 2;
      claseCuerpo.seleccionarCuerpo(2);
      delay(10);
    }
    if (prueba.equals("CUER3")) {
      bandera = false;
      cuerpo = 3;
      claseCuerpo.seleccionarCuerpo(3);
      delay(10);
    }
    if (prueba.equals("CUER4")) {
      bandera = false;
      cuerpo = 4;
      claseCuerpo.seleccionarCuerpo(4);
      delay(10);
    }
    if (prueba.equals("CUER5")) {
      bandera = false;
      cuerpo = 5;
      claseCuerpo.seleccionarCuerpo(5);
      delay(10);
    }
    if (prueba.equals("CUER6")) {
      bandera = false;
      cuerpo = 6;
      claseCuerpo.seleccionarCuerpo(6);
      delay(10);
    }
    if (prueba.equals("REGC1")) {
      Serial.println("entro en registro circunferencial 1"); 
      acRegCir = true;  //leer valores del registro circunferencial activado
      acRegLat = false; //leer valores del registro lateral desactivado
      bandera = false;
      //registroCircunferencial.cuerpo(cuerpo);
      registroCircunferencial.moverRegistro(1);
    }
    if (prueba.equals("REGC2")) {
      Serial.println("entro en registro circunferencial 2"); 
      acRegCir = true;  //leer valores del registro circunferencial activado
      acRegLat = false; //leer valores del registro lateral desactivado
      bandera = false;
      //registroCircunferencial.cuerpo(cuerpo);
      registroCircunferencial.moverRegistro(2);
    }
    if (prueba.equals("REGC3")) {
      Serial.println("entro en registro circunferencial 3"); 
      acRegCir = true;  //leer valores del registro circunferencial activado
      acRegLat = false; //leer valores del registro lateral desactivado
      bandera = false;
      //registroCircunferencial.cuerpo(cuerpo);
      registroCircunferencial.moverRegistro(3);
    }
    if (prueba.equals("REGC4")) {
      Serial.println("entro en registro circunferencial 4"); 
      acRegCir = true;  //leer valores del registro circunferencial activado
      acRegLat = false; //leer valores del registro lateral desactivado
      bandera = false;
      //registroCircunferencial.cuerpo(cuerpo);
      registroCircunferencial.moverRegistro(4);
    }

    if (prueba.equals("REGL1")) {
      Serial.println("entro en registro lateral 1");
      acRegCir = false;  //leer valores del registro circunferencial desactivado
      acRegLat = true;  //leer valores del registro circunferencial activado
      bandera = false;
      registroLateral.moverRegistro(1);
    }
    if (prueba.equals("REGL0")) {
      Serial.println("entro en registro lateral 0");
      acRegCir = false;  //leer valores del registro circunferencial desactivado
      acRegLat = true;  //leer valores del registro circunferencial activado
      bandera = false;
      registroLateral.moverRegistro(0);
    }
    if (prueba.equals("REGL2")) {
      Serial.println("entro en registro lateral 2");
      acRegCir = false;  //leer valores del registro circunferencial desactivado
      acRegLat = true;  //leer valores del registro circunferencial activado
      bandera = false;
      registroLateral.moverRegistro(2);
    }
    if (prueba.equals("REGL3")) {
      Serial.println("entro en registro lateral 3");
      acRegCir = false;  //leer valores del registro circunferencial desactivado
      acRegLat = true;  //leer valores del registro circunferencial activado
      bandera = false;
      registroLateral.moverRegistro(3);
    }
    if (prueba.equals("BGF")) {
 //     Serial.println("entro en la dir de barra ");
      //Serial.print(cuerpo);
      //barraGRaf.direccionar(cuerpo);
      
    }
    if(prueba.equals("BGV")){
      //Serial.println("entro en elcuerpo de barra");
      barraGRaf.imprimir(cuerpo);
      bandera = false;
    }    
    if(prueba.equals("BBT1")){
     Serial.println("entro en elcuerpo de barrido tinta 1");
      barridoTinta.moverRegistro(1);
      bandera = false;
    }
    if(prueba.equals("BBT2")){
     Serial.println("entro en elcuerpo de barrido tinta 2");
      barridoTinta.moverRegistro(2);
      bandera = false;
    }
    if(prueba.equals("BBT3")){
     Serial.println("entro en elcuerpo de barrido tinta mutua 3");
      barridoTinta.moverRegistro(3);
      bandera = false;
    }
    if(prueba.equals("BBT4")){
     Serial.println("entro en elcuerpo de barrido tinta 4");
      barridoTinta.moverRegistro(4);
      bandera = false;
    }
    prueba = "";
  }  
}
