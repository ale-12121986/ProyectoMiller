//Maestro
#include "ControlClavija.h"
#include "DatosDisplay.h"
#include "Iluminacion.h"
#include "Direcciones.h"
#include "Registro.h"
#include "EEPROM.h"
#include <Wire.h>
#include "WString.h"
int direccionBotones = 7;
int placaClavija1, placaClavija2, placaClavija3, placaClavija4;
int clavijas = 0, cuerpos = 0, cuerpoViejo = 0, leerPotenciometro, cuerpoViejo2 = 0;
float valor1;
String valorRegistro;
int datoBarra;
int conteo = 0;
int dirBarra1 = 0, dirBarra2 = 0, dirBarra3 = 0, dirBarra4 = 0;
boolean memoria = false, trabajo = false;
int valorTinteros[6][28];
int matricesCuerpos[6][28];
const byte Boton1 = 22;  // cuerpo anterior
const byte Boton2 = 29;  // cuerpo1
const byte Boton3 = 28;  // cuerpo2
const byte Boton4 = 26;  // cuerpo3
const byte Boton5 = 23;  // cuerpo4
const byte Boton6 = 27;  // cuerpo5
const byte Boton7 = 25;  // cuerpo6
const byte Boton8 = 24;  // selecciono cambiar
const int pot = A2;
const int pot2 = A1;
int Centena, Decena, Unidad;
int envios = 3;
//Se llama las clases
DatosDisplay datosDisplay;
ControlClavija controlarClavija;
Direcciones direccionControl;
Iluminacion iluminacion;
Registro registro;

int ejecucionDeClavija(int posicion) {
  valor1 = analogRead(pot);
  delay(5);
  leerDato(valor1);
  //Serial.println(valor1);
  datosDisplay.enviarDato(Decena, Centena, posicion);
  return valor1;
}
void enviarDatoBarra(int dato){
conteo++;
  if(conteo == 20){
    //Serial.println("se envia el dato a la barra");
    conteo = 0;
    registro.ValorBarra(dato);
    //registro.ValorBarra(dato);
  }
}
void moverRegistroC(int valor){
  registro.moverRegistroCircunferencial(valor);
  retardo10ms();
  registro.moverRegistroCircunferencial(valor);
}

void moverRegistroL(int valor){
  registro.moverRegistroLateral(valor);
  retardo10ms();
  registro.moverRegistroLateral(valor);
}
void moverRegistroBarra(int valor){
  registro.BarridoTinta(valor);
  retardo10ms();
  registro.BarridoTinta(valor);
}
void leerDato(float Valor) {
  int valor;
  valor = (Valor * 1000) / 1024;
  Centena = valor / 100;
  Decena = (valor - Centena * 100) / 10;
  Unidad = (valor - Centena * 100 - Decena * 10);
  datoBarra = Centena * 10 + Decena;

}
void ejecucionRegistro(String dato){  
  int negativo = 0;
  int valor = dato.toInt();
  valor = map(valor,0,1023,-150, 150);
  Centena = valor/100;
  //Decena = valor/10;
  Decena = (valor - Centena*100)/10;
  Unidad = (valor - Centena*100 - Decena*10);
  if (valor < 0) {
    negativo = 8;
    Centena = Centena*-1;
    Decena = Decena *-1;
    Unidad = Unidad *-1;    
  }
  datosDisplay.enviarDato(Unidad, Decena,1);
  retardo10ms();
  datosDisplay.enviarDato(Centena, negativo,2);
}

void barridoCuerpo(int cuerpos) {  //barre todos los cuerpos de las calvija e imprime todos los datos en los display
  //controlarClavija.posInicial();
  int i = 1;
  do {
    direccionesDeBotones();
    //Serial.print("leyendo clavija");
    //Serial.println(i);
    controlarClavija.leerPotIzquierdo(cuerpos, i);
    retardo50ms();
    leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro
    controlarClavija.leerPotderecho(cuerpos, i);
    retardo50ms();
    i++;
    leerPotenciometro = ejecucionDeClavija(3);
    controlarClavija.leerPotIzquierdo(cuerpos, i);
    retardo50ms();
    leerPotenciometro = ejecucionDeClavija(2);
    controlarClavija.leerPotderecho(cuerpos, i);
    retardo50ms();
    leerPotenciometro = ejecucionDeClavija(1);
    i++;
  } while (i <= 14);
}
void guardarMemoria(int cuerpos) {  //Se guarda en memoria el valor de todos los potenciometros de cada cuerpo
  int8_t dirMemoria = 0;
  for (int i = 1; i <= 14; i++) {
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

void compararValoresCuerpos(int cuerpos) {
  int valorPot = 0, valorMemoria = 0, dirMemoria = 0;
  for (int i = 1; i <= 14; i++) {
    EEPROM.get(dirMemoria, valorMemoria);
    controlarClavija.leerPotIzquierdo(cuerpos, i);
    retardo100ms();
    valorPot = analogRead(pot);
    while (valorPot < valorMemoria) {
      controlarClavija.motorIzquierdoMas(cuerpos, i);
    }
    while (valorPot > valorMemoria) {
      controlarClavija.motorIzquierdoMenos(cuerpos, i);
    }
    dirMemoria++;
    EEPROM.get(dirMemoria, valorMemoria);
    controlarClavija.leerPotderecho(cuerpos, i);
    retardo100ms();
    valorPot = analogRead(pot);
    while (valorPot < valorMemoria) {
      controlarClavija.motorDerechoMas(cuerpos, i);
    }
    while (valorPot > valorMemoria) {
      controlarClavija.motorDerechoMenos(cuerpos, i);
    }
    dirMemoria++;
  }
}

void direccionesDeBotones() {
  direccionBotones += 1;
  if (direccionBotones == 15) {
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
      dirBarra1 = 1;
      dirBarra2 = 2;
      dirBarra3 = 3;
      dirBarra4 = 4;
      break;
    case 9:
      placaClavija1 = 3;
      placaClavija2 = 3;
      placaClavija3 = 4;
      placaClavija4 = 4;
      dirBarra1 = 5;
      dirBarra2 = 6;
      dirBarra3 = 7;
      dirBarra4 = 8;
      break;
    case 10:
      placaClavija1 = 5;
      placaClavija2 = 5;
      placaClavija3 = 6;
      placaClavija4 = 6;
      dirBarra1 = 9;
      dirBarra2 = 10;
      dirBarra3 = 11;
      dirBarra4 = 12;
      break;
    case 11:
      placaClavija1 = 7;
      placaClavija2 = 7;
      placaClavija3 = 8;
      placaClavija4 = 8;
      dirBarra1 = 13;
      dirBarra2 = 14;
      dirBarra3 = 15;
      dirBarra4 = 16;
      break;
    case 12:
      placaClavija1 = 9;
      placaClavija2 = 9;
      placaClavija3 = 10;
      placaClavija4 = 10;
      dirBarra1 = 17;
      dirBarra2 = 18;
      dirBarra3 = 19;
      dirBarra4 = 20;
      break;
    case 13:
      placaClavija1 = 11;
      placaClavija2 = 11;
      placaClavija3 = 12;
      placaClavija4 = 12;
      dirBarra1 = 21;
      dirBarra2 = 22;
      dirBarra3 = 23;
      dirBarra4 = 24;
      break;
    case 14:
      placaClavija1 = 13;
      placaClavija2 = 13;
      placaClavija3 = 14;
      placaClavija4 = 14;
      dirBarra1 = 25;
      dirBarra2 = 26;
      dirBarra3 = 27;
      dirBarra4 = 28;
      break;
    default:
      break;
  }
  direccionControl.imprimirDireccion(direccionBotones);
}
void retardo50ms() {
  delay(50);
}
void retardo300ms() {
  delay(300);
}
void retardo10ms() {
  delay(10);
}
void retardo100ms() {
  delay(100);
}
void setup() {
  controlarClavija.configurar();
  datosDisplay.configurar();
  direccionControl.configurar();
  iluminacion.configurar();
  registro.Configurar();
  pinMode(Boton1, INPUT);
  pinMode(Boton2, INPUT);
  pinMode(Boton3, INPUT);
  pinMode(Boton4, INPUT);
  pinMode(Boton5, INPUT);
  pinMode(Boton6, INPUT);
  pinMode(Boton7, INPUT);
  pinMode(Boton8, INPUT);
  pinMode(pot, INPUT);
  //pinMode(poteDerecho,INPUT);
  //analogReference(DEFAULT);

  Serial.begin(115200);
  iluminacion.trabajoMemoria(0);
  iluminacion.encenderCuerpo(0);
  Serial.println("Inicio Imprenta miller");
}
void loop() {
  // put your main code here, to run repeatedly:
  controlarClavija.posInicial();
  delay(1000);
Inicio:
  direccionControl.imprimirDireccion(6);  //direccion de lk6  seleccion de M1/M2
  retardo10ms();

  while (true) {  //M1: trabajo M2: memoria
    while (digitalRead(Boton6) == LOW && digitalRead(Boton7) == LOW) {
    retardo10ms();
    }
    if (digitalRead(Boton6) == HIGH) {  // Boton M1
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
    
    if (digitalRead(Boton7) == HIGH) {  // Boton M2
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
  if (digitalRead(Boton1) == HIGH) {
    iluminacion.encenderCuerpo(7);
    Serial.println("Se selecciono el cuerpo anterior");
    cuerpoViejo2 = cuerpos;
    cuerpos = cuerpoViejo;
    iluminacion.encenderCuerpo(cuerpos);
    registro.activarCuerpos(cuerpos);
    while (digitalRead(Boton1) == HIGH) {
      retardo100ms();
    }
    iluminacion.encenderCuerpo(9);
    //registro.activarCuerpos(cuerpos);
    cuerpoViejo = cuerpoViejo2;
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  }
  if (digitalRead(Boton2) == HIGH) {
    Serial.println("Se selecciono el cuerpo1");
    cuerpoViejo = cuerpos;
    cuerpos = 1;
    registro.activarCuerpos(cuerpos);
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton2) == HIGH) {
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  } else if (digitalRead(Boton3) == HIGH) {
    Serial.println("Se selecciono el cuerpo2");
    cuerpoViejo = cuerpos;
    cuerpos = 2;
    registro.activarCuerpos(cuerpos);
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton3) == HIGH) {
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  } else if (digitalRead(Boton4) == HIGH) {
    Serial.println("Se selecciono el cuerpo3");
    cuerpoViejo = cuerpos;
    cuerpos = 3;
    registro.activarCuerpos(cuerpos);
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton4) == HIGH) {
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  } else if (digitalRead(Boton5) == HIGH) {
    Serial.println("Se selecciono el cuerpo4");
    cuerpoViejo = cuerpos;
    cuerpos = 4;
    registro.activarCuerpos(cuerpos);
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton5) == HIGH) {
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
  } else if (digitalRead(Boton6) == HIGH) {
    Serial.println("Se selecciono el cuerpo5");
    cuerpoViejo = cuerpos;
    cuerpos = 5;
    registro.activarCuerpos(cuerpos);
    iluminacion.encenderCuerpo(cuerpos);
    while (digitalRead(Boton6) == HIGH) {
      retardo100ms();
    }
    barridoCuerpo(cuerpos);
  } else if (digitalRead(Boton7) == HIGH) {
    cuerpoViejo = cuerpos;
    cuerpos = 6;
    registro.activarCuerpos(cuerpos);
    iluminacion.encenderCuerpo(cuerpos);
    Serial.println("Se selecciono el cuerpo6");
    while (digitalRead(Boton7) == HIGH) {
      retardo100ms();
    }
    if (trabajo == true) {
      barridoCuerpo(cuerpos);
    }
    if(memoria == true ){
      barridoCuerpo(cuerpos);
      goto Memoria;
    }
  } else if (digitalRead(Boton8) == HIGH) {
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
  direccionesDeBotones();  // direcciones de las clavijas
  delay(20);

  if (digitalRead(Boton7) == HIGH) {  //motor izquierdo que gira derecha
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 7(Boton izquierdo +)");
    controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija1);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra1);
    }
    while (digitalRead(Boton7) == HIGH) {
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro >= 900) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton1) == HIGH) {  //motor izquierdo que gira izquierda
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 1(Boton izquierdo -)");
    controlarClavija.motorIzquierdoMas(cuerpos, placaClavija1);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra1);
    }
    while (digitalRead(Boton1) == HIGH) {
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(4);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro <= 10) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton2) == HIGH) {  //motor derecho que gira derecha
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 2(Boton Boton Derecho +)");
    controlarClavija.motorDerechoMenos(cuerpos, placaClavija2);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra2);
    }
    while (digitalRead(Boton2) == HIGH) {
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(3);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro >= 900) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton6) == HIGH) {  //motor derecho que gira izquierda
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 6(Boton Derecho -)");
    controlarClavija.motorDerechoMas(cuerpos, placaClavija2);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra2);
    }
    while (digitalRead(Boton6) == HIGH) {
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(3);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro <= 110) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton4) == HIGH) {  //motor izquierdo que girai derecha
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 4(Boton izquierdo +)");
    controlarClavija.motorIzquierdoMenos(cuerpos, placaClavija3);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra3);
    }
    while (digitalRead(Boton4) == HIGH) {
      leerPotenciometro = ejecucionDeClavija(2);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro >= 900) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo50ms();
  }

  if (digitalRead(Boton3) == HIGH) {  //motor izquierdo que gira izquierda
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 3(Boton izquierdo -)");
    controlarClavija.motorIzquierdoMas(cuerpos, placaClavija3);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra3);
    }
    while (digitalRead(Boton3) == HIGH) {
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(2);
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro <= 100) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton8) == HIGH) {  //motor derecho que gira derecha
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 8(Boton Boton Derecho +)");
    controlarClavija.motorDerechoMenos(cuerpos, placaClavija4);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra4);
    }
    while (digitalRead(Boton8) == HIGH) {
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(1);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro >= 900) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }

  if (digitalRead(Boton5) == HIGH) {  //motor derecho que gira izquierda
    controlarClavija.posInicial();
    direccionControl.imprimirLaDireccion();
    Serial.println("Boton 5(Boton Derecho -)");
    controlarClavija.motorDerechoMas(cuerpos, placaClavija4);
    for (int i = 0; i < 2; i++) {
      registro.DireccionBarra(dirBarra4);
    }
    while (digitalRead(Boton5) == HIGH) {
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(1);  //va a la rutina de escribir en los display y trae el valor del potenciometro
      enviarDatoBarra(datoBarra);
      if (leerPotenciometro <= 100) {
        controlarClavija.resetflipflop();
      }
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }
  direccionControl.imprimirDireccion(4);  //cambiar de cuerpo
  if (digitalRead(Boton1) == HIGH && digitalRead(Boton2) == HIGH && digitalRead(Boton3) == HIGH && digitalRead(Boton4) == HIGH && digitalRead(Boton5) == HIGH && digitalRead(Boton6) == HIGH && digitalRead(Boton7) == HIGH && digitalRead(Boton8) == HIGH) {
    retardo50ms();
    goto trabajoCuerpo;
  }

  direccionControl.imprimirDireccion(6);  //direccion de lk6  seleccion de M1/M2
  if (digitalRead(Boton6) == HIGH || digitalRead(Boton7) == HIGH) {
    goto Inicio;
  }
  if(digitalRead(Boton2) == HIGH){    //Boton menos mutual stting module 
    Serial.println("Boton 2(Boton Boton + mutual stting module)");
    moverRegistroBarra(2);
    while (digitalRead(Boton2) == HIGH) {
      retardo50ms();
      //leerPotenciometro = ejecucionDeClavija(2);
    }
    moverRegistroBarra(4);
  }
  if(digitalRead(Boton1) == HIGH){    //Boton menos mutual stting module 
    Serial.println("Boton 1(Boton Boton - mutual stting module)");
    moverRegistroBarra(3);
    while (digitalRead(Boton1) == HIGH) {
      retardo50ms();
      //leerPotenciometro = ejecucionDeClavija(2);
    }
    moverRegistroBarra(4);
  }

  //---------------Registro circunferencial-------------------------
  direccionControl.imprimirDireccion(2);  //Diereccion para registro circunferencial
    
    if(digitalRead(Boton5) == LOW){  //incrementar
      Serial.println("Se activa el Registro circunferencial mas");
      moverRegistroC(2);
      while(digitalRead(Boton5) == LOW){
        retardo10ms();
        valorRegistro = registro.leerTransmisor();
        ejecucionRegistro(valorRegistro);
      }
      moverRegistroC(4);
    }
    
    if(digitalRead(Boton1) == LOW){  //decrementar
      Serial.println("Se activa el registro circunferencial menos");
      moverRegistroC(3);
      while(digitalRead(Boton1) == LOW){
        retardo10ms();
        valorRegistro = registro.leerTransmisor();
        ejecucionRegistro(valorRegistro);
      }
      moverRegistroC(4);
    }
    if(digitalRead(Boton8) == LOW){  //centrar
      Serial.println("Se activa el registro circunferencial centrar");
      moverRegistroC(1);
      while(digitalRead(Boton8) == LOW){
        retardo50ms();
        valorRegistro = registro.leerTransmisor();
        ejecucionRegistro(valorRegistro);
      }
      moverRegistroC(4);
    }
  // -------------------Registro lateral-----------------------------   
  direccionControl.imprimirDireccion(3);  //Diereccion para registro lateral

    if(digitalRead(Boton5) == LOW){  //incrementar
      Serial.println("Se activa el Registro lateral mas");
      moverRegistroL(2);
      while(digitalRead(Boton5) == LOW){
        valorRegistro = registro.leerTransmisor();
        ejecucionRegistro(valorRegistro);
      }
      moverRegistroL(0);
    }
    if(digitalRead(Boton1) == LOW){  //decrementar
      Serial.println("Se activa el registro lateral menos");
      moverRegistroL(3);
      while(digitalRead(Boton1) == LOW){
        valorRegistro = registro.leerTransmisor();
        ejecucionRegistro(valorRegistro);
      }
      moverRegistroL(0);
    }
    if(digitalRead(Boton8) == LOW){  //centrar
      Serial.println("Se activa el registro lateral centrar");
      moverRegistroL(1);
      while(digitalRead(Boton8) == HIGH){
        valorRegistro = registro.leerTransmisor();
        ejecucionRegistro(valorRegistro);
      }
      moverRegistroL(0);
    }
  //------------fuente de tinta
  direccionControl.imprimirDireccion(5);

  if(digitalRead(Boton5) == LOW){  //incrementar
    controlarClavija.posInicial();
    Serial.println("Boton 1(Boton Boton + fuente de tinta)");
    controlarClavija.motorIzquierdoMas(cuerpos, 0);
    while(digitalRead(Boton5) == LOW){
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(1);
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }
  if(digitalRead(Boton1) == LOW){  //decrementar
    controlarClavija.posInicial();
    Serial.println("Se activa el registro lateral menos");
    controlarClavija.motorIzquierdoMenos(cuerpos, 0);
    while(digitalRead(Boton1) == LOW){
      retardo50ms();
      leerPotenciometro = ejecucionDeClavija(1);
    }
    controlarClavija.resetflipflop();
    retardo10ms();
  }
  retardo10ms();
  goto trabajoCuerpo;
Memoria:
  retardo300ms();
  retardo300ms();
  memoria = true;
  guardarMemoria(cuerpos);
  goto Inicio;
}
