#define BUZZER_PIN 8

int frecvente[] = {
  31, 33, 35, 37, 39, 41,
  44, 46, 49, 52, 55, 58
};

const int nrNote = sizeof(frecvente) / sizeof(frecvente[0]);
const int durataNota = 250;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void redaNota(int f) {
  tone(BUZZER_PIN, f, durataNota);
  delay(durataNota + 50);
  noTone(BUZZER_PIN);
}

void loop() {

  for(int i = 0; i < nrNote; i++) {
    redaNota(frecvente[i]);
  }

  for(int i = nrNote - 1; i >= 0; i--) {
    redaNota(frecvente[i]);
  }

  delay(800);
}
