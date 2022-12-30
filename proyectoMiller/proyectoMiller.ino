#include "ControlClavija.h"
#include "DatosDisplay.h"

#include "Direcciones.h"
int direccionBotones = 7;
int placaClavija1, placaClavija2, placaClavija3, placaClavija4;
int clavijas = 0, aa = 0, cuerpos = 0, cuerpoViejo = 0, leerPotenciometro;
int* leerDisplay;
int arr[3];

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
const int pot = A0;
//const int poteDerecho = A1;
int Centena, Decena, Unidad; 

DatosDisplay datosDisplay;
ControlClavija controlarClavija;
Direcciones direccionControl;

void leerDato (float Valor){
  Valor= (Valor*100)/1023;
  Centena = Valor/100;
  Decena = (Valor - Centena*100)/10;
  Unidad = (Valor - Centena*100 - Decena*10);
  // Serial.print("Centena: ");
  // Serial.println(Centena);
  // Serial.print("Decena: ");
  // Serial.println(Decena);
  // Serial.print("Unidad: ");
  // Serial.println(Unidad);
}

void barridoCuerpo(int cuerpos){ //barre todos los cuerpos de las calvija e imprime todos los datos en los display
  //controlarClavija.posInicial();
  for (int i=1; i <= 15; i++) {
    aa++;
    Serial.print("leyendo clavija");
    Serial.println(i);
    if (aa == 5) aa = 1; 
      controlarClavija.leerPotIzquierdo(cuerpos, i);
      valor1 = analogRead(pot);
      leerDato(valor1);
      datosDisplay.enviarDato(Unidad, Decena, aa);
      aa++;
      valor1 = analogRead(pot);
      leerDato(valor1);
      datosDisplay.enviarDato(Unidad, Decena, aa);
    }
}
int ejecucionDeClavija(int posicion){
  valor1 = analogRead(pot);
  delay(5);
  leerDato(valor1);
  Serial.println(valor1);
  datosDisplay.enviarDato(Unidad, Decena, posicion);
  
  return valor1;
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
void setup() {
  controlarClavija.configurar();
  datosDisplay.configurar();
  direccionControl.configurar();
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
  Serial.println("Inicio Imprenta miller");
}

void loop() {
  // put your main code here, to run repeatedly:
  controlarClavija.posInicial();
  delay(1000);
  Inicio:
  direccionControl.imprimirDireccion(6); //direccion de lk6  seleccion de M1/M2
  delay(10);
  
  while (true) {//M1: trabajo M2: memoria
    while (digitalRead(Boton6) == LOW && digitalRead(Boton7) == LOW) {
    }
    if(digitalRead(Boton6 == HIGH) ){// Boton M1
      while (digitalRead(Boton6) == HIGH) {    
      delay(50);
       //Serial.println("Se preciono M1 y se va a trabajo");
      }
      delay(50);
      memoria = false;
      trabajo = true;
      Serial.println("Se preciono M1 y se va a trabajo");
      goto Trabajar;
    }
    if(digitalRead(Boton7 == HIGH)){ // Boton M2
      while (digitalRead(Boton7) == HIGH) {    
      delay(50);
      }
      trabajo = false;
      memoria = true;
      Serial.println("Se preciono M2 y se va a memoria");
      //goto Memoria;
      goto Trabajar;
    }
  }
  Trabajar:
  delay(1000);
  direccionControl.imprimirDireccion(4);
  while (digitalRead(Boton1) == LOW && digitalRead(Boton2) == LOW && digitalRead(Boton3) == LOW && digitalRead(Boton4) == LOW && digitalRead(Boton5) == LOW && digitalRead(Boton6) == LOW && digitalRead(Boton7) == LOW && digitalRead(Boton8) == LOW) {
  delay(150);
  }
  trabajoCuerpo:
  //direccionControl.imprimirDireccion(4);// Direccion de las placas de seleccionar cuerpo
  delay(10);
    if(digitalRead(Boton1) == HIGH){
      Serial.println("Se selecciono el cuerpo anterior");
      cuerpos = cuerpoViejo;
      while (digitalRead(Boton1) == HIGH) {
        delay(300);    
      }
      barridoCuerpo(cuerpos);
    }
    if(digitalRead(Boton2) == HIGH){
      Serial.println("Se selecciono el cuerpo1");
      cuerpoViejo = cuerpos;
      cuerpos = 1;
      while (digitalRead(Boton2) == HIGH) {    
        delay(300);
      }
      barridoCuerpo(cuerpos);
    }
    if(digitalRead(Boton3) == HIGH){
      cuerpoViejo = cuerpos;
      cuerpos = 2;
      Serial.println("Se selecciono el cuerpo2");
      while (digitalRead(Boton3) == HIGH) {    
        delay(300);
      }
      barridoCuerpo(cuerpos);
    }
    if(digitalRead(Boton4) == HIGH){
      cuerpoViejo = cuerpos;
      cuerpos = 3;
      Serial.println("Se selecciono el cuerpo3");
      while (digitalRead(Boton4) == HIGH) {    
        delay(300);
      }
      barridoCuerpo(cuerpos);
    }
    if(digitalRead(Boton5) == HIGH){
      cuerpoViejo = cuerpos;
      cuerpos = 4;
      Serial.println("Se selecciono el cuerpo4");
      while (digitalRead(Boton5) == HIGH) {    
        delay(300);
      }
      barridoCuerpo(cuerpos);
    }
    if(digitalRead(Boton6) == HIGH){
      cuerpoViejo = cuerpos;
      cuerpos = 5;
      Serial.println("Se selecciono el cuerpo5");
      while (digitalRead(Boton6) == HIGH) {    
        delay(300);
      }
      barridoCuerpo(cuerpos);
    }
    if(digitalRead(Boton7) == HIGH){
      cuerpoViejo = cuerpos;
      cuerpos = 6;
      Serial.println("Se selecciono el cuerpo6");
      while (digitalRead(Boton7) == HIGH) {    
        delay(50);
      }
      barridoCuerpo(cuerpos);      
    }
    if(digitalRead(Boton8) == HIGH){
      //cuerpos = 90;
      //posCuerpo = 6;
      Serial.println("Se selecciono cambiar");
      while (digitalRead(Boton8) == HIGH) {    
      delay(300);
      }
    }
  delay(200);
  Tinteros:
  direccionesDeBotones(); // direcciones de las clavijas
  delay(20);
 
  if (digitalRead(Boton7) == HIGH) {  //motor izquierdo que gira derecha
    controlarClavija.posInicial();
    Serial.println("Boton 7(Boton izquierdo +)");
    controlarClavija.motorIzquierdoMas(cuerpos, placaClavija1);
    while (digitalRead(Boton7) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro 
      if (leerPotenciometro >= 900) {
        if(trabajo == true){
          //controlarClavija.motorIzquierdoMas(cuerpos, placaClavija1);
          controlarClavija.resetflipflop();          
        }else if(memoria == true){  
        
        }
      } 
    }
    controlarClavija.resetflipflop();
    delay(50);
  }

  if (digitalRead(Boton1) == HIGH) {  //motor izquierdo que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 1(Boton izquierdo -)");
    controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija1);
    while (digitalRead(Boton1) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro <= 10) {
        if(trabajo == true){
          //controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija1);  //va a la rutina de escribir en los display y trae el valor del potenciometro          
          controlarClavija.resetflipflop();
        }          
      }
    }
    controlarClavija.resetflipflop();
    delay(50);
  }

  if (digitalRead(Boton2) == HIGH) {  //motor derecho que gira derecha
    controlarClavija.posInicial();
    Serial.println("Boton 2(Boton Boton Derecho +)");
    controlarClavija.motorDerechoMas(cuerpos, placaClavija2);
    while (digitalRead(Boton2) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(3);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if(leerPotenciometro >= 900) {
        //controlarClavija.motorDerechoMas(cuerpos, placaClavija2);  //va a la rutina de escribir en los display y trae el valor del potenciometro
        controlarClavija.resetflipflop();    
      }
    }    
    controlarClavija.resetflipflop();
    delay(50);
  }

  if (digitalRead(Boton6) == HIGH) {  //motor derecho que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 6(Boton Derecho -)");
    controlarClavija.motorDerechoMenos(cuerpos, placaClavija2);
    while (digitalRead(Boton6) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(3);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro <= 10) {
        //controlarClavija.motorDerechoMenos(cuerpos, placaClavija2); //va a la rutina de escribir en los display y trae el valor del potenciometro
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    delay(50);
  }

  if(digitalRead(Boton4) == HIGH) {  //motor izquierdo que girai derecha
    controlarClavija.posInicial();
    Serial.println("Boton 4(Boton izquierdo +)");
    controlarClavija.motorIzquierdoMas(cuerpos, placaClavija3);
    while (digitalRead(Boton4) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(2);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro >= 900) {
        //controlarClavija.motorIzquierdoMas(cuerpos, placaClavija3); //va a la rutina de escribir en los display y trae el valor del potenciometro
        controlarClavija.resetflipflop();          
      }
    }
    controlarClavija.resetflipflop();
    delay(50);
  }

  if (digitalRead(Boton3) == HIGH) {  //motor izquierdo que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 3(Boton izquierdo -)");
    controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija3);
    while (digitalRead(Boton3) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(2);
      if (leerPotenciometro <= 10) {
        //controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija3); //va a la rutina de escribir en los display y trae el valor del potenciometro
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    delay(50);
  }

  if (digitalRead(Boton8) == HIGH) {  //motor derecho que gira derecha
    controlarClavija.posInicial();
    Serial.println("Boton 8(Boton Boton Derecho +)");
    controlarClavija.motorDerechoMas(cuerpos, placaClavija4);           
    while (digitalRead(Boton8) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(1);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro >= 900) {
        //controlarClavija.motorDerechoMas(cuerpos, placaClavija4); //va a la rutina de escribir en los display y trae el valor del potenciometro
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    delay(50);
  }
  
  if (digitalRead(Boton5) == HIGH) {  //motor derecho que gira izquierda
    controlarClavija.posInicial();
    Serial.println("Boton 5(Boton Derecho -)");
    controlarClavija.motorDerechoMenos(cuerpos, placaClavija4);
    while (digitalRead(Boton5) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(1);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      if (leerPotenciometro <= 10) {
       // controlarClavija.motorDerechoMenos(cuerpos, placaClavija4);
        controlarClavija.resetflipflop();        
      }
    }
    controlarClavija.resetflipflop();
    delay(50);
  }
  direccionControl.imprimirDireccion(4);
  if (digitalRead(Boton1) == HIGH &&digitalRead(Boton2) == HIGH && digitalRead(Boton3) == HIGH && digitalRead(Boton4) == HIGH && digitalRead(Boton5) == HIGH && digitalRead(Boton6) == HIGH && digitalRead(Boton7) == HIGH && digitalRead(Boton8) == HIGH) {
    delay(10);
    goto trabajoCuerpo;
  }
  goto Tinteros;
  //goto trabajoCuerpo;
  delay(5);
Memoria:  
  delay(5);
}