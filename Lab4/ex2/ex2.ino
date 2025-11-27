byte codCifre[10] = {
  B00000011, B11110011, B00100101, B01100001, B11010001,
  B01001001, B00001001, B11100011, B00000001, B01000001
};

byte selectDigit[4] = {31, 47, 79, 143};

unsigned long timp[10];
int valori[10];

void setup() {
  pinMode(4, OUTPUT); 
  pinMode(7, OUTPUT);  
  pinMode(8, OUTPUT);  

  Serial.begin(9600);
  randomSeed(analogRead(A0));

  Serial.println("Test de reactie - introdu rapid numarul!");
  delay(1500);
}

void afisare(byte cod, byte digitMask) {
  digitalWrite(4, LOW);
  shiftOut(8, 7, LSBFIRST, cod);
  shiftOut(8, 7, LSBFIRST, digitMask);
  digitalWrite(4, HIGH);
}

void afiseazaNumar(int nr) {
  int c[4];

  for (int i = 3; i >= 0; i--) {
    c[i] = nr % 10;
    nr /= 10;
  }

  for (int k = 0; k < 40; k++)
    for (int d = 0; d < 4; d++)
      afisare(codCifre[c[d]], selectDigit[d]);
}

void loop() {

  for (int incercare = 0; incercare < 10; incercare++) {

    int numar = random(1000, 9999);
    valori[incercare] = numar;

    unsigned long start = millis();
    bool gata = false;

    while (!gata) {

      afiseazaNumar(numar);

      // verificare scriere
      if (Serial.available()) {
        String s = Serial.readStringUntil('\n');
        s.trim();

        if (s.toInt() == numar) {
          gata = true;
          timp[incercare] = millis() - start;
          Serial.print("Corect! Timp: ");
          Serial.print(timp[incercare]);
          Serial.println(" ms");
        } else {
          Serial.println("Gresit! Mai incearca.");
        }
      }
    }

    delay(300);
  }

  // statistici simple
  unsigned long total = 0;
  unsigned long minT = timp[0], maxT = timp[0];

  for (int i = 0; i < 10; i++) {
    if (timp[i] < minT) minT = timp[i];
    if (timp[i] > maxT) maxT = timp[i];
    total += timp[i];
  }

  float medie = total / 10.0;

  Serial.println("\n--- REZULTAT FINAL ---");
  Serial.print("Minim: "); Serial.print(minT); Serial.println(" ms");
  Serial.print("Maxim: "); Serial.print(maxT); Serial.println(" ms");
  Serial.print("Medie: "); Serial.print(medie); Serial.println(" ms");

  while (1); 
}