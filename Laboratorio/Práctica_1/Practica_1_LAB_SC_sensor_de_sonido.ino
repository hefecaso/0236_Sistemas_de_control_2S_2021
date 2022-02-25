#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int echo = 5;
int trig = 4;
int led_verde = 6;
int buzer = 7;
int led_rojo = 8;
int t_duration;
int distance;


void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_rojo, OUTPUT);
  pinMode(buzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  t_duration = pulseIn(echo, HIGH);//funcion que devuelve el valor de tiempo en responder
  distance = 0.01715*t_duration; //distancia del sensor al objeto                                  //el pin echo, y ya se tiene el tiemo en µs en ir y volver el pulso

    
   if(distance >50 and distance <101){
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_rojo, LOW);
  digitalWrite(buzer, LOW);
  Serial.print(distance);
  Serial.println(" cm");
  lcd.setCursor(0,0);
  lcd.print("DISTANCIA: "); 
  lcd.setCursor(11,0);
  lcd.print(distance); 
  lcd.setCursor (0,1);
  lcd.setCursor(14,0);
  lcd.print("cm");
  lcd.setCursor (0,1);
  lcd.print("RANGO 1");
  lcd.display();
  delay(500);
  lcd.clear(); 
  }else if(distance >25 and distance <51){
  digitalWrite(led_verde, LOW);
  digitalWrite(led_rojo, LOW);
  digitalWrite(buzer, HIGH);
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print(distance);
  Serial.println(" cm");
  lcd.setCursor(0,0);
  lcd.print("DISTANCIA: "); 
  lcd.setCursor(11,0);
  lcd.print(distance); 
  lcd.setCursor (0,1);
  lcd.setCursor(14,0);
  lcd.print("cm");
  lcd.setCursor (0,1);
  lcd.print("RANGO 2");
  lcd.display();
  delay(500);
  lcd.clear();    
  }else if(distance <26){
  digitalWrite(led_verde, LOW);
  digitalWrite(led_rojo, HIGH);
  digitalWrite(buzer, LOW);
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print(distance);
  Serial.println(" cm");
  lcd.setCursor(0,0);
  lcd.print("DISTANCIA: "); 
  lcd.setCursor(11,0);
  lcd.print(distance);
  lcd.setCursor(14,0);
  lcd.print("cm"); 
  lcd.setCursor (0,1);
  lcd.print("RANGO 3");
  lcd.display();
  delay(500);
  lcd.clear();    
  }
      

}
