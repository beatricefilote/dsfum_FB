unsigned long lvl13 = 0;
int step13 = 5;
unsigned long prev13 = 0;
int speed13 = 20;

unsigned long lvl12 = 0;
int step12 = 3;
unsigned long prev12 = 0;
int speed12 = 30;

int period = 5;  

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  if (now - prev13 >= speed13) {
    prev13 = now;
    lvl13 += step13;
    if (lvl13 >= 255 || lvl13 == 0) {
      step13 = -step13;
    }
  }

  int cycle13 = now % period;
  int duty13 = (lvl13 * period) / 255;
  digitalWrite(13, cycle13 < duty13);


  if (now - prev12 >= speed12) {
    prev12 = now;
    lvl12 += step12;
    if (lvl12 >= 255 || lvl12 == 0) {
      step12 = -step12;
    }
  }

  int cycle12 = now % period;
  int duty12 = (lvl12 * period) / 255;
  digitalWrite(12, cycle12 < duty12);
}