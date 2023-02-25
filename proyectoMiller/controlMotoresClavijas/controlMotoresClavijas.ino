//const byte i = 61;
//const byte k = 60;
//const byte j = 59;
//const byte l = 58;
//const byte h = 57;
//int pote1 = A0;
//int pote2 = A1;
//const byte izquierdaBotonMas = 5;
//const byte derechaBotonMas = 4;
//const byte izquierdaBotonMenos = 3;
//const byte derechaBotonMenos = 2;
void setup() {
  // put your setup code here, to run once:
  //pinMode(i, OUTPUT);
  //pinMode(k, OUTPUT);
  //pinMode(j, OUTPUT);
  //pinMode(l, OUTPUT);
  //pinMode(h, OUTPUT);
  //pinMode(izquierdaBotonMas, INPUT);
  //pinMode(derechaBotonMas, INPUT);
  //pinMode(izquierdaBotonMenos, INPUT);
  //pinMode(derechaBotonMenos, INPUT);
  //DDRK = B11111111;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(i, LOW);
  digitalWrite(k, LOW);
  digitalWrite(j, HIGH);
  digitalWrite(h, HIGH);
  if (digitalRead(izquierdaBotonMas) == HIGH) {  //motor izquierdo que girai derecha
    while (digitalRead(izquierdaBotonMas) == HIGH) {
      digitalWrite(h, HIGH);
      digitalWrite(i, HIGH);
      digitalWrite(k, LOW);
      digitalWrite(l, HIGH);
      delay(10);
      digitalWrite(l, LOW);
      digitalWrite(j, LOW);
    }
    digitalWrite(j, HIGH);
  }
  if (digitalRead(izquierdaBotonMenos) == HIGH) {  //motor izquierdo que gira izquierda
    while (digitalRead(izquierdaBotonMenos) == HIGH) {
      digitalWrite(h, HIGH);
      digitalWrite(i, LOW);
      digitalWrite(k, HIGH);
      digitalWrite(l, HIGH);
      delay(10);
      digitalWrite(l, LOW);
      digitalWrite(j, LOW);
    }
    digitalWrite(j, HIGH);
  }
  if (digitalRead(derechaBotonMas) == HIGH) {  //motor derecho que gira derecha
    while (digitalRead(izquierdaBotonMas) == HIGH) {
      digitalWrite(h, LOW);
      digitalWrite(i, HIGH);
      digitalWrite(k, LOW);
      digitalWrite(l, HIGH);
      delay(10);
      digitalWrite(l, LOW);
      digitalWrite(j, LOW);
    }
    digitalWrite(j, HIGH);
  }
  if (digitalRead(izquierdaBotonMenos) == HIGH) {  //motor derecho que gira izquierda
    while (digitalRead(izquierdaBotonMenos) == HIGH) {
      digitalWrite(h, LOW);
      digitalWrite(i, LOW);
      digitalWrite(k, HIGH);
      digitalWrite(l, HIGH);
      delay(10);
      digitalWrite(l, LOW);
      digitalWrite(j, LOW);
    }
    digitalWrite(j, HIGH);
  }
}