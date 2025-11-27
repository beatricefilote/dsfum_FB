unsigned long level = 0;    
int change = 6;             
unsigned long lastUpdate = 0;
int updateDelay = 25;       
int period = 4;             

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  if (now - lastUpdate >= updateDelay) {
    lastUpdate = now;

    level += change;

    //  intorc sensul
    if (level >= 255 || level == 0) {
      change = -change;
    }
  }

  unsigned long timeInCycle = now % period;

  unsigned long duty = (level * period) / 255;

  if (timeInCycle < duty)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
}