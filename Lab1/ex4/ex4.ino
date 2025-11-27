void setup() {
  for(int p = 8; p <= 13; p++) {
    pinMode(p, OUTPUT);
  }
}

int curent = 8;

void loop() {

  digitalWrite(curent, HIGH);
  delay(250);   

  digitalWrite(curent, LOW);
  delay(250);

  curent++;

  // >13 => ma intorc
  if (curent > 13) {
    curent = 8;
  }
}