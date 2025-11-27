void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  int t = millis();
  
  while( millis()-t < 20)
  {
    if( millis()-t < 10)
      digitalWrite(13, 1);
    else
      digitalWrite(13,0);
  }
}