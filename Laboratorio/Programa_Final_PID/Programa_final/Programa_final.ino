#include <SoftwareSerial.h>

SoftwareSerial miBT(0,1);   // pin 10 como RX, pin 11 como TX
//Declarando los del ultrasónico
int echo = 4;
int trig = 5;
int t_duration;
int distance;

//Declarando LEDS

int LEDR = 34;
int LEDA = 36;
int Buzzer = 38;


//Vamos con los motores
int mot_d = 6;
int mot_i = 7;
int forward_d = 30;
int forward_i = 31;
int backward_d = 37;
int backward_i = 35;
//Luego los encoders

const int channelPinA = 2;
const int channelPinB = 3;

//Variables para encoder derecho

float PPR = 102;
volatile int ISRCounter_d = 0;
unsigned int pulsos_d = 0;
unsigned long Time_d = 0;
unsigned int RPM_d = 0;

//Variables para encoder izquierdo

volatile int ISRCounter_i = 0;
unsigned int pulsos_i = 0;
unsigned long Time_i = 0;
unsigned int RPM_i = 0;

void setup(/* arguments */) {
  /* code */
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(forward_d, OUTPUT);
  pinMode(forward_i, OUTPUT);
  pinMode(backward_d, OUTPUT);
  pinMode(backward_i, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDA, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  pinMode(channelPinA, INPUT_PULLUP);
  pinMode(channelPinB, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Listo");  // escribe Listo en el monitor
  miBT.begin(38400);    // comunicacion serie entre Arduino y el modulo a 38400 
  attachInterrupt(digitalPinToInterrupt(channelPinA), doEncode_d, CHANGE);
  attachInterrupt(digitalPinToInterrupt(channelPinB), doEncode_i, CHANGE);
  Time_d = millis();
  Time_i = millis();
}


void loop(/* arguments */) {
  /* code */
  
  //Funcion del Bluetooth
  if (miBT.available())       // si hay informacion disponible desde modulo
  Serial.write(miBT.read());   // lee Bluetooth y envia a monitor serial de Arduino

  if (Serial.available())     // si hay informacion disponible desde el monitor serial
  miBT.write(Serial.read());   // lee monitor serial y envia a Bluetooth

  //Funcion del Sensor Ultrasonico
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  t_duration = pulseIn(echo, HIGH);//funcion que devuelve el valor de tiempo en responder
  distance = 0.01715*t_duration; //distancia del sensor al objeto
  //Serial.print(distance);
  //Serial.println(" cm");

//Lectura de distancias y velocidad del motor

if(millis() - Time_d >=100 && millis() - Time_i >=100){
  // Medicion de velocidad Motor Derecho
    pulsos_d = ISRCounter_d;
    RPM_d = 60*pulsos_d/PPR;

    //Serial.print("Pulsos por segundo A:");
    //Serial.println(pulsos_d);

    Serial.print("Revoluciones por minuto Derecho:");
    Serial.println(RPM_d);
    //se reestablecen los valores
    ISRCounter_d = 0;
    pulsos_d = 0;
    Time_d = millis();

    

  // Medicion de velocidad Motor Izquierdo
    pulsos_i = ISRCounter_i;
    RPM_i = 60*pulsos_i/PPR;

    //Serial.print("Pulsos por segundo Izquierdo:");
    //Serial.println(pulsos_i);

    Serial.print("Revoluciones por minuto Izquierdo:");
    Serial.println(RPM_i);
    //se reestablecen los valores
    ISRCounter_i = 0;
    pulsos_i = 0;
    Time_i = millis();
}
    if(100<distance ){
        accion(255,255,1,1,0,0,0,0,0);
        //Serial.println("accion1");
    }
    else if(50<distance && distance<= 100){
        accion(191,191,1,1,0,0,1,0,0);
        //Serial.println("accion2");
    }
    else if(40<distance  && distance<=50){
        accion(95,95,1,1,0,0,0,0,1);
        //Serial.println("accion3");
    }
    else if(25<distance  && distance<=40){
        accion(65,65,1,1,0,0,0,0,1);
        //Serial.println("accion4");
    }
    else if(20<distance && distance <=25){
        accion(191,191,0,0,1,1,0,1,0);
        //Serial.println("accion5");
    }
    else{
        accion(0,0,0,0,0,0,0,1,0);
        //Serial.println("accion6");
    }
  if(RPM_d==0 && Time_d > 2000){
    accion(0,0,0,0,0,0,0,1,0);
    delay(500);
  }
  if(RPM_i==0 && Time_i > 2000){
    accion(0,0,0,0,0,0,0,1,0); 
    delay(500); 
  }
}
    

void accion(int motD,int motI,int forD,int forI,int backD,int backI,int ledA,int ledD,int bufferr){
    analogWrite(mot_d,motD);
    analogWrite(mot_i,motI);
    digitalWrite(forward_d, forD);
    digitalWrite(forward_i, forI);
    digitalWrite(backward_d, backD);
    digitalWrite(backward_i, backI);
    digitalWrite(LEDA, ledA);
    digitalWrite(LEDR, ledD);
    digitalWrite(Buzzer, bufferr);
}


void doEncode_d()
{
  ISRCounter_d++;
}

void doEncode_i()
{
  ISRCounter_i++;
}
