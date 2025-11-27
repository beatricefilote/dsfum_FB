void setup() {
  pinMode(4, OUTPUT);  
  pinMode(7, OUTPUT);  
  pinMode(8, OUTPUT);  
}

void loop() {

  byte codSegment[10] = {
    B00000011, // 0
    B11110011, // 1
    B00100101, // 2
    B01100001, // 3
    B11010001, // 4
    B01001001, // 5
    B00001001, // 6
    B11100011, // 7
    B00000001, // 8
    B01000001  // 9
  };

  byte digitSelect[4] = { 31, 47, 79, 143 };

  for (int digit = 0; digit < 4; digit++) {

    for (int cifra = 0; cifra < 10; cifra++) {

      trimiteLaDisplay(codSegment[cifra], digitSelect[digit]);
      delay(1000);   
    }
  }
}

void trimiteLaDisplay(byte seg, byte digitMask) {
  digitalWrite(4, LOW);           
  shiftOut(8, 7, LSBFIRST, seg);  
  shiftOut(8, 7, LSBFIRST, digitMask);
  digitalWrite(4, HIGH);        
}