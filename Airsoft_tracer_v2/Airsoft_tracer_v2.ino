#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensor=4;
int led=5;
int up=7;
int down=8;
unsigned int timing;

void setup() {
  Serial.begin(9600);
  Serial.println("initializing");
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  timing=EEPROM.read(1);M
  lcd.begin(); 
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("AirSoftTracer");
  lcd.setCursor(0,1);
  lcd.print("TimerSet :");
  lcd.setCursor(10,1);
  lcd.print(timing);
  lcd.setCursor(14,1);
  lcd.print("ms");
  //delay(300);
}

void loop() {
  ledOn();
  if(digitalRead(up)==LOW){
    timing++;
    EEPROM.update(1, timing);
    Serial.println(timing);
    lcd.setCursor(10,1);
    lcd.print("   ");
    lcd.setCursor(10,1);
    lcd.print(timing);
    delay(100);
  }
  if(digitalRead(down)==LOW && timing>=1){
    timing--;
    EEPROM.update(1, timing);
    Serial.println(timing);
    lcd.setCursor(10,1);
    lcd.print("   ");
    lcd.setCursor(10,1);
    lcd.print(timing);
    delay(100);
  }
}
void ledOn (){
  if(digitalRead(sensor)==HIGH){
    Serial.println(sensor);
    digitalWrite(led, HIGH); //lampu nyala
    delay(timing); //durasi nyala
    digitalWrite(led, LOW); //lampu mati
    delay(timing); //kalo mau tanpa spasi hapus ini
  }
}

