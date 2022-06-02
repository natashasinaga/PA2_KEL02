#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define enA A0
#define in1 4
#define in2 5

// HX711 circuit wiring
float hasil, berat ;
int motorSpeedA = 0;
int motorSpeedB = 0;
int motorSpeedC = 0;
int motorSpeedD = 0;
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;  

LiquidCrystal_I2C lcd(0x27, 16, 2);
HX711 scale;


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin (9600); 
  
  Serial.println("Pastikan Tidak Ada Beban");
  lcd.begin();
  lcd.backlight();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(440.0);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(50);				        // reset the scale to 0
  Serial.println("Silahkan Untuk Menimbang");
}

void loop() {
   
    
  Serial.print("Berat");
  float berat= scale.get_units(25);
  if(berat<=0.1)
  {
    berat=0.0;
  }
  Serial.println(berat,1);
  
  if (berat<1000)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SILAHKAN TIMBANG");
  lcd.setCursor(0, 1);
  lcd.print("Berat= ");
  lcd.print(berat,1);
  lcd.print(" g");  
  analogWrite(enA, motorSpeedB);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  }
  
 else if (berat>=1000)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SILAHKAN TIMBANG");
  float hasil=berat/100;
  lcd.setCursor(0, 1);
  lcd.print("Berat= ");
  lcd.print(hasil);
  lcd.print(" kg");
  }
    
  scale.power_down();
  delay(2000);
  scale.power_up();

    

  if ( berat == 0){
    digitalWrite(enA, motorSpeedA);
    if ( motorSpeedA == 0 ){
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);
      }
    }

    else if ( berat >= 10 && berat == 100){
    digitalWrite(enA, motorSpeedB);
    if ( motorSpeedB == 1000 ){
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);
      }
    }
    
}
 

    
    
  

