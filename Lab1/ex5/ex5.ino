void setup() {
  for (int p = 8; p <= 13; p++) {
    pinMode(p, OUTPUT);
  }
}

void loop() {
  unsigned long t = millis();
  int pozitie = (t / 300) % 11;  
  int pinAprins;

  if (pozitie < 6) {
    pinAprins = 8 + pozitie;          //  8 - 13
  } else {
    pinAprins = 13 - (pozitie - 5);   // 13 - 8
  }

  digitalWrite(pinAprins, HIGH);

  for (int p = 8; p <= 13; p++) {
    if (p != pinAprins) digitalWrite(p, LOW);
  }
}