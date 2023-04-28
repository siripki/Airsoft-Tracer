#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
  
int up=HIGH;       // Don't Touch!
int dn=HIGH;       // Don't Touch!
int cutoff=5;      // Don't Touch!
int led=6;         // Don't Touch!
int i=0;           // Don't Touch!
int m=0;           // Don't Touch!
int n=1;           // Don't Touch!
int dly=50;        // Don't Touch!
int kill=65;       // Don't Touch!
int set=0;         // Don't Touch! 
int maxKill=149;   // Set Engine Max cutoff Time (milisecs) or just don't touch it!
int minKill=41;    // Set Engine Min cutoff Time (milisecs) or just don't touch it!
int maxDly=499;    // Set Engine Min delay Time (milisecs) or just don't touch it!
int minDly=51;     // Set Engine Min delay Time (milisecs) or just don't touch it!
unsigned long prevMillisConf = 0;  // Don't Touch!
const long saveInterval = 1700;    // Set Timeout

void setup() {
  Serial.begin(9600);
  Serial.println("initializing");
  lcd.begin(); 
  lcd.backlight();
  lcd.setCursor(10,0);
  lcd.print("Haruhi");
  delay(500);
  lcd.setCursor(3,1);
  lcd.print("Quick Shifter");
  pinMode(7, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(8, INPUT);
  pinMode(cutoff, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(cutoff, LOW);
  dly=EEPROM.read(256);
  kill=EEPROM.read(257);
  digitalWrite(led, HIGH);
  Serial.println("Ready.");
  delay(1500);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Ready");
  delay(450);
  lcd.setCursor(5,1);
  lcd.print("To ");
  delay(200);
  lcd.print("Race!");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(1,0);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(2,0);
  lcd.print(char(4));
  lcd.setCursor(0,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(3,0);
  lcd.print(char(4));
  lcd.setCursor(1,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(4,0);
  lcd.print(char(4));
  lcd.setCursor(2,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(5,0);
  lcd.print(char(4));
  lcd.setCursor(3,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(6,0);
  lcd.print(char(4));
  lcd.setCursor(4,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(7,0);
  lcd.print(char(4));
  lcd.setCursor(5,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(8,0);
  lcd.print(char(4));
  lcd.setCursor(6,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(9,0);
  lcd.print(char(4));
  lcd.setCursor(7,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(10,0);
  lcd.print(char(4));
  lcd.setCursor(8,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(11,0);
  lcd.print(char(4));
  lcd.setCursor(9,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(12,0);
  lcd.print(char(4));
  lcd.setCursor(10,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(13,0);
  lcd.print(char(4));
  lcd.setCursor(11,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(14,0);
  lcd.print(char(4));
  lcd.setCursor(12,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(15,0);
  lcd.print(char(4));
  lcd.setCursor(13,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(16,0);
  lcd.print(char(4));
  lcd.setCursor(14,2);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(15,1);
  lcd.print(char(4));
  delay(25);
  lcd.setCursor(16,1);
  lcd.print(char(4));
  delay(100);
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("Ready.");
}

void loop() {
  unsigned long saveMillis = millis();
  int swstate=digitalRead(7);
  int snsrstate=digitalRead(2);
  int up=digitalRead(3);
  int dn=digitalRead(4);
  if (set==3) {
    set=0;
  }
  if(saveMillis - prevMillisConf > saveInterval) {
    if (n==0) {
      n=1;
      if (i==1) {
        Serial.print("Disabled");
        digitalWrite(led, LOW);
        lcd.clear();
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("Disabled"); 
        lcd.setCursor(1,1);
        lcd.print("Clutch Pulled.");
        delay(250);
      }
      if (i==0) {
        lcd.clear();
        lcd.setCursor(5,1);
        lcd.print("Ready.");
        Serial.println("Ready.");
      }
    }
  }
  if(saveMillis - prevMillisConf < saveInterval) {
    n=0;
  }
  if (i==2) {
    i=0;
  }
  if (dly>maxDly) {
    dly=maxDly;
  }
  if (dly<minDly) {
    dly=minDly;
  }
  if (kill>maxKill) {
    kill=maxKill;
  }
  if (kill<minKill) {
    kill=minKill;
  }
  if (up==LOW && dn==LOW) {
    switch (set) {
    case 0:
      set+=1;
      lcd.backlight();
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Unlocked");
      lcd.setCursor(4,1);
      lcd.print("Setting.");
      delay(550);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Delay Time:    +");
      lcd.setCursor(1,1);
      lcd.print(dly);
      lcd.setCursor(4,1);
      lcd.print("ms");
      lcd.setCursor(15,1);
      lcd.print("-");
    break;
    case 1:
      set+=1;
      lcd.backlight();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cut-off Time:  +");
      lcd.setCursor(1,1);
      lcd.print(kill);
      lcd.setCursor(4,1);
      lcd.print("ms");
      lcd.setCursor(15,1);
      lcd.print("-");
    break;
    case 2:
      set+=1;
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Locked");
      lcd.setCursor(3,1);
      lcd.print("and Saved.");
      EEPROM.write(256, dly);
      EEPROM.write(257, kill);
      delay(500);
    break;
    }
  }
  if (up==LOW) {
    if (set==1) {
      lcd.backlight();
      delay(100);
      dly+=10;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Delay Time:    +");
      lcd.setCursor(1,1);
      lcd.print(dly);
      lcd.setCursor(4,1);
      lcd.print("ms");
      lcd.setCursor(15,1);
      lcd.print("-");
      prevMillisConf = millis();
    }
    if (set==2) {
      lcd.backlight();
      delay(100);
      kill+=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cut-off Time:  +");
      lcd.setCursor(1,1);
      lcd.print(kill);
      lcd.setCursor(4,1);
      lcd.print("ms");
      lcd.setCursor(15,1);
      lcd.print("-");
      prevMillisConf = millis();
    }
  }
  if (dn==LOW) {
    if (set==1) {
      lcd.backlight();
      delay(100);
      dly-=10;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Delay Time:    +");
      lcd.setCursor(1,1);
      lcd.print(dly);
      lcd.setCursor(4,1);
      lcd.print("ms");
      lcd.setCursor(15,1);
      lcd.print("-");
      prevMillisConf = millis();
    }
    if (set==2) {
      lcd.backlight();
      delay(100);
      kill-=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cut-off Time:  +");
      lcd.setCursor(1,1);
      lcd.print(kill);
      lcd.setCursor(4,1);
      lcd.print("ms");
      lcd.setCursor(15,1);
      lcd.print("-");
      prevMillisConf = millis();
    }
  }
  switch (swstate) {
    case LOW:
    if (i==0) {
      i+=1;
      Serial.print("Disabled");
      digitalWrite(led, LOW);
      lcd.clear();
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Disabled");
      lcd.setCursor(1,1);
      lcd.print("Clutch Pulled.");
      delay(250);
    }
    break;
    case HIGH:
    if (i==1) {
      i+=1;
      Serial.println("Enabled");
      digitalWrite(led, HIGH);
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Ready.");
      delay(250);
    }
    break;
  }

  switch (snsrstate) {
    case LOW:
    cutoffengine();
    break;
    case HIGH:
    m=0;
    delay(50);
    break;
  }
}

void cutoffengine() {
    if (i==0 && m==0) {
      m+=1;
      Serial.println("Gear UP");
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Gear Up.");
      digitalWrite(cutoff, HIGH);
      digitalWrite(led, LOW);
      delay(kill);
      digitalWrite(cutoff, LOW);
      digitalWrite(led, HIGH);
      delay(dly);
      Serial.println("Ready.");
      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Ready.");
    }
}
