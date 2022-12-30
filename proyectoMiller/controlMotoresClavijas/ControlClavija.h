class ControlClavija{
  private:

  const byte i = 61;
  const byte k = 60;
  const byte j = 59;
  const byte l =58;
  const byte h=57;
  int pote1 = A0;
  int pote2 = A1;
  const byte izquierdaBotonMas = 5;
  const byte derechaBotonMas = 4;
  const byte izquierdaBotonMenos = 3;
  const byte derechaBotonMenos = 2;
  int direccion;
  int selecMotor;
  int datos[2];
  public:

  void configurar(){
    pinMode(i, OUTPUT);
    pinMode(k, OUTPUT);
    pinMode(j, OUTPUT);
    pinMode(l, OUTPUT);
    pinMode(h, OUTPUT);
    pinMode(izquierdaBotonMas,INPUT);
    pinMode(derechaBotonMas,INPUT);
    pinMode(izquierdaBotonMenos,INPUT);
    pinMode(derechaBotonMenos,INPUT);
    DDRK = B11111111;
  }
  void int[] enviarDatoPot(){
    return datos[] {0,0};
  }
  void activarMotorIzquierdoMas(int direccion){
    PORTK = direccion;
    digitalWrite(h, HIGH);
    digitalWrite(i, HIGH);
    digitalWrite(k, LOW);
    digitalWrite(l, HIGH);
    delay(10);
    digitalWrite(l, LOW);
    digitalWrite(j, LOW);
    
  }
   void activarMotorIzquierdoMenos(){

   }
}