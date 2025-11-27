#include <LedControl.h>

LedControl lc(12, 10, 11, 1);

byte cur[8];
byte nxt[8];
byte last[8];

bool getCell(byte g[8], int r, int c) {
  if (r < 0 || r > 7 || c < 0 || c > 7) return 0;
  return (g[r] >> c) & 1;
}

byte neighbors(byte g[8], int r, int c) {
  byte n = 0;
  for (int dr = -1; dr <= 1; dr++)
    for (int dc = -1; dc <= 1; dc++)
      if (!(dr == 0 && dc == 0))
        n += getCell(g, r + dr, c + dc);
  return n;
}

void step() {
  for (int r = 0; r < 8; r++) {
    nxt[r] = 0;
    for (int c = 0; c < 8; c++) {
      byte alive = getCell(cur, r, c);
      byte n = neighbors(cur, r, c);
      if ((alive && (n == 2 || n == 3)) || (!alive && n == 3))
        nxt[r] |= (1 << c);
    }
  }
}

void show(byte g[8]) {
  for (int r = 0; r < 8; r++)
    lc.setRow(0, r, g[r]);
}

bool same(byte a[8], byte b[8]) {
  for (int i = 0; i < 8; i++)
    if (a[i] != b[i]) return false;
  return true;
}

bool dead(byte g[8]) {
  for (int i = 0; i < 8; i++)
    if (g[i] != 0) return false;
  return true;
}

void randomGrid() {
  for (int i = 0; i < 8; i++)
    cur[i] = random(0, 256);
  if (dead(cur)) randomGrid();
}

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  randomSeed(analogRead(A0));
  randomGrid();
  show(cur);
}

void loop() {
  delay(200);

  for (int i = 0; i < 8; i++) last[i] = cur[i];

  step();
  show(nxt);

  for (int i = 0; i < 8; i++) cur[i] = nxt[i];

  if (dead(cur) || same(cur, last)) {
    delay(300);
    randomGrid();
    show(cur);
  }
}