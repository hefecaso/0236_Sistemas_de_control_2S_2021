#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27,16,2);

int echo = 1;
int trig = 2;
int pwm1 = 5;
int pwm2 = 6;

void setup() {
  //lcd.init();
  //lcd.clear();
  //lcd.backlight(); //para encender luz del led

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzer, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
}

//Nota importante: Eliminamos la programación de la pantalla LCD, debido a que genera
//conflictos con los motores, sujeto a cambios sobre si agregarlo.

void loop() {
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  t_duration = pulseIn(echo, HIGH);//funcion que devuelve el valor de tiempo en responder
  distance = 0.01715*t_duration; //distancia del sensor al objeto                                  //el pin echo, y ya se tiene el tiemo en µs en ir y volver el pulso


  if(distance > 100){
    dc = 100;
    analogWrite(pwm1,255);
    analogWrite(pwm2,255);
  //lcd.setCursor(0,0);
  //lcd.print("DISTANCIA: ");
  //lcd.setCursor(11,0);
  //lcd.print(distance);
  //lcd.setCursor(14,0);
  //lcd.print("cm");
  //lcd.setCursor(0,1);
  //lcd.print("%DC: ");
  //lcd.setCursor(5,1);
  //lcd.print(dc);
  //lcd.setCursor (9,1);
  //lcd.print("%");
  //lcd.display();
  delay(500);
  lcd.clear();
}else if(distance <= 100 and distance >=51){
    dc = 75;
    analogWrite(pwm1,191);
    analogWrite(pwm2,191);
  //lcd.setCursor(0,0);
  //lcd.print("DISTANCIA: ");
  //lcd.setCursor(11,0);
  //lcd.print(distance);
  //lcd.setCursor(14,0);
  //lcd.print("cm");
  //lcd.setCursor(0,1);
  //lcd.print("%DC: ");
  //lcd.setCursor(5,1);
  //lcd.print(dc);
  //lcd.setCursor (9,1);
  //lcd.print("%");
  //lcd.display();
  delay(500);
  lcd.clear();
}else if(distance >=26 and distance <=50){
    dc = 50;
    analogWrite(pwm1,127);
    analogWrite(pwm2,127);
  //lcd.setCursor(0,0);
  //lcd.print("DISTANCIA: ");
  //lcd.setCursor(11,0);
  //lcd.print(distance);
  //lcd.setCursor(14,0);
  //lcd.print("cm");
  //lcd.setCursor(0,1);
  //lcd.print("%DC: ");
  //lcd.setCursor(5,1);
  //lcd.print(dc);
  //lcd.setCursor (9,1);
  //lcd.print("%");
  //lcd.display();
  delay(500);
  lcd.clear();
}else if(distance >=0 and distance <=25){
      dc = 0;
      analogWrite(pwm1,0);
      analogWrite(pwm2,0);
    //lcd.setCursor(0,0);
    //lcd.print("DISTANCIA: ");
    //lcd.setCursor(11,0);
    //lcd.print(distance);
    //lcd.setCursor(14,0);
    //lcd.print("cm");
    //lcd.setCursor(0,1);
    //lcd.print("%DC: ");
    //lcd.setCursor(5,1);
    //lcd.print(dc);
    //lcd.setCursor (9,1);
    //lcd.print("%");
    //lcd.display();
    delay(500);
    //lcd.clear();
    }


}
