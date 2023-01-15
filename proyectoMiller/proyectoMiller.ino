#include "ControlClavija.h"
#include "DatosDisplay.h"
#include "Iluminacion.h"
#include "Direcciones.h"
#include "EEPROM.h"
int direccionBotones = 7;
int placaClavija1, placaClavija2, placaClavija3, placaClavija4;
int clavijas = 0, cuerpos = 0, cuerpoViejo = 0, leerPotenciometro;
float valor1;
boolean memoria = false, trabajo = false;
int valorTinteros[6][28];
int matricesCuerpos[6][28];
const byte Boton1 = 5;  // 9
const byte Boton2 = 2;  // 8
const byte Boton3 = 9;  // 7
const byte Boton4 = 8;  // 6
const byte Boton5 = 6;  // 5
const byte Boton6 = 3;  // 4
const byte Boton7 = 4;  // 3
const byte Boton8 = 7;  // 2
const int pot = A2;
const int pot2 = A1;
int Centena, Decena, Unidad; 
//Se llama las clases
DatosDisplay datosDisplay;
ControlClavija controlarClavija;
Direcciones direccionControl;
Iluminacion iluminacion;

int ejecucionDeClavija(int posicion){
  valor1 = analogRead(pot);
  delay(5);
  leerDato(valor1);
  Serial.println(valor1);
  datosDisplay.enviarDato(Decena, Centena, posicion);
  return valor1;
}

void leerDato (float Valor){
  float valor;
  valor= (Valor*1000)/1024;
  Centena = valor/100;
  Decena = (valor - Centena*100)/10;
  Unidad = (valor - Centena*100 - Decena*10);
  Serial.print("Centena: ");
  Serial.println(Centena);
  Serial.print("Decena: ");
  Serial.println(Decena);
  Serial.print("Unidad: ");
  Serial.println(Unidad);
}

void barridoCuerpo(int cuerpos){  //barre todos los cuerpos de las calvija e imprime todos los datos en los display
  //controlarClavija.posInicial();
  int i=1;
  do {
    direccionesDeBotones();
    Serial.print("leyendo clavija");
    Serial.println(i); 
    controlarClavija.leerPotIzquierdo(cuerpos, i);
    retardo100ms();
    leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro
    controlarClavija.leerPotderecho(cuerpos, i);
    retardo100ms();
    i++;
    leerPotenciometro = ejecucionDeClavija(3);
    controlarClavija.leerPotIzquierdo(cuerpos, i);
    retardo100ms();
    leerPotenciometro = ejecucionDeClavija(2);
    controlarClavija.leerPotderecho(cuerpos, i);
    retardo100ms();
    leerPotenciometro = ejecucionDeClavija(1);
    i++;
  }while (i<=14);      
}
void guardarMemoria(int cuerpos){   //Se guarda en memoria el valor de todos los potenciometros de cada cuerpo
  int8_t dirMemoria = 0;
  for (int i= 1; i<= 14; i++){
    controlarClavija.leerPotIzquierdo(cuerpos, i);
    retardo100ms(); 
    valor1 = analogRead(pot);
    EEPROM.put(dirMemoria, valor1);
    dirMemoria++;
    controlarClavija.leerPotderecho(cuerpos, i);
    retardo100ms(); 
    valor1 = analogRead(pot);
    EEPROM.put(dirMemoria, valor1);
    dirMemoria++;
  }
}

void compararValoresCuerpos(int cuerpos){
  int valorPot = 0, valorMemoria = 0, dirMemoria = 0;
  for(int i = 1; i<=14; i++){
    EEPROM.get(dirMemoria, valorMemoria);
    controlarClavija.leerPotIzquierdo(cuerpos, i);
    retardo100ms(); 
    valorPot = analogRead(pot);
    while (valorPot < valorMemoria) {
    controlarClavija.motorIzquierdoMas(cuerpos, i);
    }  
    while(valorPot > valorMemoria) {
      controlarClavija.motorIzquierdoMenos(cuerpos, i);
    }
    dirMemoria++;
    EEPROM.get(dirMemoria, valorMemoria);
    controlarClavija.leerPotderecho(cuerpos, i);
    retardo100ms();
    valorPot =analogRead(pot);
    while (valorPot < valorMemoria) {
    controlarClavija.motorDerechoMas(cuerpos, i);
    }  
    while(valorPot > valorMemoria) {
      controlarClavija.motorDerechoMenos(cuerpos, i);
    }             
    dirMemoria++;    
  }      
}

void direccionesDeBotones(){
  direccionBotones+=1;
  if(direccionBotones == 15){
    direccionBotones = 8;
  }
  //Serial.print("LK");
  //Serial.println(direccionBotones);
  switch (direccionBotones) {
    case 8:
      placaClavija1 = 1;
      placaClavija2 = 1;
      placaClavija3 = 2;
      placaClavija4 = 2;      
      break;
    case 9:
      placaClavija1 = 3;
      placaClavija2 = 3;
      placaClavija3 = 4;
      placaClavija4 = 4;

      break;
    case 10:
      placaClavija1 = 5;
      placaClavija2 = 5;
      placaClavija3 = 6;
      placaClavija4 = 6;
      break;
    case 11:
      placaClavija1 = 7;
      placaClavija2 = 7;
      placaClavija3 = 8;
      placaClavija4 = 8;
      break;
    case 12:
      placaClavija1 = 9;
      placaClavija2 = 9;
      placaClavija3 = 10;
      placaClavija4 = 10;
      break;
    case 13:
      placaClavija1 = 11;
      placaClavija2 = 11;
      placaClavija3 = 12;
      placaClavija4 = 12;
      break;
    case 14:
      placaClavija1 = 13;
      placaClavija2 = 13;
      placaClavija3 = 14;
      placaClavija4 = 14;
      break;
    default:
    break;
    }
  direccionControl.imprimirDireccion(direccionBotones);
}
void retardo50ms(){
  delay(50);  
}
void retardo300ms(){
  delay(300);  
}
void retardo10ms(){
  delay(10);
}
void retardo100ms(){
  delay(100);
}
void setup() {
  controlarClavija.configurar();
  datosDisplay.configurar();
  direccionControl.configurar();
  iluminacion.configurar();
  pinMode(Boton1,INPUT);
  pinMode(Boton2,INPUT);
  pinMode(Boton3,INPUT);
  pinMode(Boton4,INPUT);
  pinMode(Boton5,INPUT);
  pinMode(Boton6,INPUT);
  pinMode(Boton7,INPUT);
  pinMode(Boton8,INPUT);
  pinMode(pot,INPUT);
  //pinMode(poteDerecho,INPUT);
  //analogReference(DEFAULT);
  Serial.begin(9600);
  iluminacion.trabajoMemoria(0);
  iluminacion.encenderCuerpo(0);
  Serial.println("Inicio Imprenta miller");
}
void loop() {
  // put your main code here, to run repeatedly:
  controlarClavija.posInicial();
  delay(1000);
  Inicio:
  direccionControl.imprimirDireccion(6); //direccion de lk6  seleccion de M1/M2
  retardo10ms();
  while (true) {//M1: trabajo M2: memoria
    while (digitalRead(Boton6) == LOW && digitalRead(Boton7) == LOW) {
    }
    if(digitalRead(Boton6 == HIGH) ){// Boton M1
      while (digitalRead(Boton6) == HIGH) {    
      retardo10ms();
       //Serial.println("Se preciono M1 y se va a trabajo");
      }
      memoria = false;
      trabajo = true;
      iluminacion.trabajoMemoria(1);
      Serial.println("Se preciono M1 y se va a trabajo");
      retardo300ms();
      goto Trabajar;
    }
    if(digitalRead(Boton7 == HIGH)){ // Boton M2
      while (digitalRead(Boton7) == HIGH) {    
      retardo50ms();
      }
      trabajo = false;
      memoria = true;
      iluminacion.trabajoMemoria(2);
      Serial.println("Se preciono M2 y se va a memoria");
      //goto Memoria;
      goto Trabajar;
    }
  }
  Trabajar:
  direccionControl.imprimirDireccion(4);
  while (digitalRead(Boton1) == LOW && digitalRead(Boton2) == LOW && digitalRead(Boton3) == LOW && digitalRead(Boton4) == LOW && digitalRead(Boton5) == LOW && digitalRead(Boton6) == LOW && digitalRead(Boton7) == LOW && digitalRead(Boton8) == LOW) {
  retardo50ms();
  }
  trabajoCuerpo:
  direccionControl.imprimirDireccion(4);
  //direccionControl.imprimirDireccion(4);// Direccion de las placas de seleccionar cuerpo
  if(digitalRead(Boton1) == HIGH){
    Serial.println("Se selecciono el cuerpo anterior");
    cuerpos = cuerpoViejo;
    while (digitalRead(Boton1) == HIGH) {
      retardo100ms();    
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
    
  }
  if(digitalRead(Boton2) == HIGH){
    Serial.println("Se selecciono el cuerpo1");
    cuerpoViejo = cuerpos;
    cuerpos = 1;
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton2) == HIGH) {    
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  }
  if(digitalRead(Boton3) == HIGH){
    Serial.println("Se selecciono el cuerpo2");
    cuerpoViejo = cuerpos;
    cuerpos = 2;
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton3) == HIGH) {    
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  }
  if(digitalRead(Boton4) == HIGH){
    Serial.println("Se selecciono el cuerpo3");
    cuerpoViejo = cuerpos;
    cuerpos = 3;
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton4) == HIGH) {    
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  }
  if(digitalRead(Boton5) == HIGH){
    Serial.println("Se selecciono el cuerpo4");
    cuerpoViejo = cuerpos;
    cuerpos = 4;
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton5) == HIGH) {    
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  }
  if(digitalRead(Boton6) == HIGH){
    Serial.println("Se selecciono el cuerpo5");
    cuerpoViejo = cuerpos;
    cuerpos = 5;
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton6) == HIGH) {    
      retardo100ms();
    }
    barridoCuerpo(cuerpos);
  }
  if(digitalRead(Boton7) == HIGH){
    cuerpoViejo = cuerpos;
    cuerpos = 6;
    iluminacion.encenderCuerpo(cuerpos);
    Serial.println("Se selecciono el cuerpo6");
    while (digitalRead(Boton7) == HIGH) {    
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);        
    }      
  }
  if(digitalRead(Boton8) == HIGH){
    //cuerpos = 90;
    //posCuerpo = 6;
    Serial.println("Se selecciono cambiar");
    while (digitalRead(Boton8) == HIGH) {    
    retardo100ms();
    }
  }
  if (trabajo == true) {
    goto Tinteros;
  }    
  Tinteros:
  direccionesDeBotones(); // direcciones de las clavijas
  delay(20);
 
  if (digitalRead(Boton7) == HIGH) {  //motor izquierdo que gira derecha
    controlarClavija.posInicial();
    Serial.println("Boton 7(Boton izquierdo +)");
    controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija1);
    while (digitalRead(Boton7) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro 
      if (leerPotenciometro >= 900) {
          controlarClavija.resetflipflop();          
      } 
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton1) == HIGH) {  //motor izquierdo que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 1(Boton izquierdo -)");
    controlarClavija.motorIzquierdoMas(cuerpos, placaClavija1);
    while (digitalRead(Boton1) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro <= 10) {
          controlarClavija.resetflipflop();          
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton2) == HIGH) {  //motor derecho que gira derecha
    controlarClavija.posInicial();
    Serial.println("Boton 2(Boton Boton Derecho +)");
    controlarClavija.motorDerechoMenos(cuerpos, placaClavija2);
    while (digitalRead(Boton2) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(3);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if(leerPotenciometro >= 900) {
        controlarClavija.resetflipflop();    
      }
    }    
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton6) == HIGH) {  //motor derecho que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 6(Boton Derecho -)");
    controlarClavija.motorDerechoMas(cuerpos, placaClavija2);
    while (digitalRead(Boton6) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(3);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro <= 10) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if(digitalRead(Boton4) == HIGH) {  //motor izquierdo que girai derecha
    controlarClavija.posInicial();
    Serial.println("Boton 4(Boton izquierdo +)");
    controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija3);
    while (digitalRead(Boton4) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(2);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro >= 900) {
        controlarClavija.resetflipflop();          
      }
    }
    controlarClavija.resetflipflop();
    retardo50ms();
  }

  if (digitalRead(Boton3) == HIGH) {  //motor izquierdo que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 3(Boton izquierdo -)");
    controlarClavija.motorIzquierdoMas(cuerpos, placaClavija3);
    while (digitalRead(Boton3) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(2);
      if (leerPotenciometro <= 100) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton8) == HIGH) {  //motor derecho que gira derecha
    controlarClavija.posInicial();
    Serial.println("Boton 8(Boton Boton Derecho +)");
    controlarClavija.motorDerechoMenos(cuerpos, placaClavija4);           
    while (digitalRead(Boton8) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(1);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro >= 900) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }
  
  if (digitalRead(Boton5) == HIGH) {  //motor derecho que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 5(Boton Derecho -)");
    controlarClavija.motorDerechoMas(cuerpos, placaClavija4);
    while (digitalRead(Boton5) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(1);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro <= 100) {
        controlarClavija.resetflipflop();        
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }  
  //direccionControl.imprimirDireccion(4);  //cambiar de cuerpo
  //if (digitalRead(Boton1) == HIGH && digitalRead(Boton2) == HIGH && digitalRead(Boton3) == HIGH && digitalRead(Boton4) == HIGH && digitalRead(Boton5) == HIGH && digitalRead(Boton6) == HIGH && digitalRead(Boton7) == HIGH && digitalRead(Boton8) == HIGH) {
  //  retardo50ms();
  //  goto trabajoCuerpo;
 // }
  
  // direccionControl.imprimirDireccion(6); //direccion de lk6  seleccion de M1/M2
  // if (digitalRead(Boton6) == HIGH && digitalRead(Boton7) == HIGH) {
  //   goto Inicio;
  // }
  
  goto trabajoCuerpo;
  
  Memoria:
  memoria = true; 
  guardarMemoria(cuerpos);
  goto Trabajar;
  
}