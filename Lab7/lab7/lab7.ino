#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte f0[8] = {B00100,B01110,B00100,B01110,B00100,B01010,B10001,B00000};
byte f1[8] = {B00100,B01110,B00100,B01100,B00110,B01010,B01001,B00000};
byte f2[8] = {B00100,B01110,B00100,B01110,B00100,B10001,B01010,B00000};
byte f3[8] = {B00100,B01110,B00100,B00110,B01100,B01010,B10010,B00000};
byte puff[8] = {B00000,B00000,B00100,B00000,B00000,B00100,B00000,B00000};

int pos = -1;
int row = 1;
int frame = 0;

unsigned long lastMove = 0;
unsigned long lastFrame = 0;
unsigned long speedMove = 120;
unsigned long speedFrame = 90;

bool paused = false;
unsigned long lastToggle = 0;

int readKey() {
  int x = analogRead(A0);
  if (x < 50) return 0;   
  if (x < 200) return 1;  
  if (x < 400) return 2;  
  if (x < 600) return 3;  
  if (x < 800) return 4;  
  return -1;
}

void showHeader() {
  lcd.setCursor(0,0);
  lcd.print("spd:");
  lcd.print(speedMove);
  lcd.print(paused ? " PAU " : " RUN ");
}

void setup() {
  lcd.begin(16,2);
  lcd.clear();

  lcd.createChar(0,f0);
  lcd.createChar(1,f1);
  lcd.createChar(2,f2);
  lcd.createChar(3,f3);
  lcd.createChar(4,puff);

  showHeader();
}

void handleKeys() {
  int k = readKey();

  if (k == 1) {      
    if (speedMove > 30) speedMove -= 10;
    showHeader();
  }

  if (k == 2) {      
    if (speedMove < 400) speedMove += 10;
    showHeader();
  }

  if (k == 4) {      
    unsigned long t = millis();
    if (t - lastToggle > 200) {
      paused = !paused;
      lastToggle = t;
      showHeader();
    }
  }
}

void loop() {
  handleKeys();

  if (paused) return;

  unsigned long t = millis();

  if (t - lastFrame >= speedFrame) {
    lastFrame = t;
    frame++;
    if (frame > 3) frame = 0;
  }

  if (t - lastMove >= speedMove) {
    lastMove = t;

    if (pos >= 0 && pos < 16) {
      lcd.setCursor(pos, row);
      lcd.write((uint8_t)4); 
    }

    if (pos-2 >= 0 && pos-2 < 16) {
      lcd.setCursor(pos-2, row);
      lcd.print(" ");
    }

    pos++;

    if (pos >= 16) {
      for (int i=0; i<16; i++) {
        lcd.setCursor(i,row);
        lcd.print(" ");
      }
      pos = -1;
      row = (row==0?1:0);
    }

    if (pos >= 0 && pos < 16) {
      lcd.setCursor(pos, row);
      lcd.write((uint8_t)frame);
    }
  }
}