
struct LedInfo {
  bool activ = false;
  String mod = "off";
  unsigned long interval = 0;
  unsigned long ultimulTimp = 0;
  int lumina = 0;      
  int directie = 1;   
};

LedInfo leduri[14];
String buffer;

void setup() {
  Serial.begin(9600);
  for (int p = 0; p < 14; p++) {
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
  }
  Serial.println("Introdu comenzi: pin,mod,interval");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      proceseazaComanda(buffer);
      buffer = "";
    } else if (c != '\r') {
      buffer += c;
    }
  }

  unsigned long acum = millis();
  for (int p = 0; p < 14; p++) {
    if (leduri[p].activ) {
      actualizeazaLED(p, acum);
    }
  }
}

void proceseazaComanda(String s) {
  s.trim();
  int c1 = s.indexOf(',');
  int c2 = s.indexOf(',', c1 + 1);

  if (c1 < 0 || c2 < 0) {
    Serial.println("Format invalid");
    return;
  }

  int pin = s.substring(0, c1).toInt();
  String mod = s.substring(c1 + 1, c2);
  unsigned long timp = s.substring(c2 + 1).toInt();

  if (pin < 0 || pin > 13) {
    Serial.println("Pin invalid");
    return;
  }

  leduri[pin].activ = true;
  leduri[pin].mod = mod;
  leduri[pin].interval = timp;
  leduri[pin].ultimulTimp = millis();

  if (mod == "fadein") leduri[pin].lumina = 0;
  if (mod == "fadeout") leduri[pin].lumina = 255;
  leduri[pin].directie = 1;

  Serial.print("OK -> pin ");
  Serial.print(pin);
  Serial.print(" mod ");
  Serial.println(mod);
}

void actualizeazaLED(int pin, unsigned long acum) {
  LedInfo &L = leduri[pin];

  if (L.mod == "on") {
    digitalWrite(pin, HIGH);
    return;
  }

  if (L.mod == "off") {
    digitalWrite(pin, LOW);
    return;
  }

  if (L.mod == "blink") {
    if (acum - L.ultimulTimp >= L.interval) {
      L.ultimulTimp = acum;
      int st = digitalRead(pin);
      digitalWrite(pin, !st);
    }
    return;
  }

  if (L.mod == "fadein" || L.mod == "fadeout") {

    unsigned long pas = L.interval / 255;
    if (pas < 1) pas = 1;

    if (acum - L.ultimulTimp >= pas) {
      L.ultimulTimp = acum;

      if (L.mod == "fadein") {
        L.lumina++;
        if (L.lumina > 255) L.lumina = 255;
      }

      if (L.mod == "fadeout") {
        L.lumina--;
        if (L.lumina < 0) L.lumina = 0;
      }
    }

    int perioada = 5;
    unsigned long faza = acum % perioada;
    int onTime = (L.lumina * perioada) / 255;
    digitalWrite(pin, faza < onTime);
  }
}