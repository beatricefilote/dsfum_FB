void setup() {
  for (int p = 8; p <= 13; p++) {
    pinMode(p, OUTPUT);
  }
}

void blinkLed8() {
  int stare = (millis() / 1000) % 2;   
  digitalWrite(8, stare);
}

void blinkLed9() {
  int stare = (millis() / 3000) % 2;  
  digitalWrite(9, stare);
}

void loop() {
  blinkLed8();
  blinkLed9();
}