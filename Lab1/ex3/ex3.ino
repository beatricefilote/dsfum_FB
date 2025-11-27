void setup() {
  for (int p = 8; p <= 13; p++) {
    pinMode(p, OUTPUT);
  }
}

void afiseazaBinar(int k) {
  for (int bit = 0; bit < 6; bit++) {
    int stare = (k >> bit) & 1;   
    digitalWrite(8 + bit, stare); 
  }
}

void loop() {
  int valoare = (millis() % 6400) / 100;  // nr intre 0 si 63
  afiseazaBinar(valoare);                
}