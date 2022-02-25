#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int volt1 = 1;
int volt2 = 2;
int pwm = 5;
int puls_menos = 8;
int puls_mas = 9;
int opcion = 10;
int pot = A0;
int dc = 0;
int velocidad = 63;
int dc_dos = 25;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(volt1, OUTPUT);
  pinMode(volt2, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(puls_menos, INPUT);
  pinMode(puls_mas, INPUT);
  pinMode(opcion, INPUT);
  Serial.begin(9600);
}

void loop() {
  int estado_opcion = digitalRead(opcion);
  int estado_pot = analogRead(pot);
  int nuevo_pot = map(estado_pot,0,1023,0,255);
  
  digitalWrite(volt1,HIGH);
  digitalWrite(volt2,LOW); 
  if(estado_opcion == HIGH){
    if(nuevo_pot >= 0 and nuevo_pot <= 127){
      analogWrite(pwm,127);
      dc = 50;
    }else if(nuevo_pot >= 128 and nuevo_pot <= 191){
      analogWrite(pwm,191);
      dc = 75;
    }else if(nuevo_pot >= 192){
      analogWrite(pwm,255);
      dc = 100;
    }
    lcd.setCursor(0,0);
    lcd.print("%DC: "); 
    lcd.setCursor(5,0);
    lcd.print(dc); 
    lcd.setCursor (9,0);
    lcd.print("%");
    lcd.display();
    delay(500);
    lcd.clear();
    dc = 0;
  }else if(estado_opcion == LOW){
    int puls_menos_ = digitalRead(puls_menos);
    int puls_mas_ = digitalRead(puls_mas);
    
      if(puls_mas_ == HIGH and velocidad < 191){
        velocidad = velocidad + 64;
        analogWrite(pwm,velocidad);
        dc_dos = dc_dos + 25;  
        delay(500); 
      }
     if(puls_menos_ == HIGH and velocidad > 63){
        velocidad = velocidad-64;
        analogWrite(pwm,velocidad);
        dc_dos = dc_dos - 25;
        delay(500);
     }
    lcd.setCursor(0,0);
    lcd.print("%DC: "); 
    lcd.setCursor(5,0);
    lcd.print(dc_dos); 
    lcd.setCursor (9,0);
    lcd.print("%");
    lcd.display();
    delay(500);
    lcd.clear();
    }
  }
