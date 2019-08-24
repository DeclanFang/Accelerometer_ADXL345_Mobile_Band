// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digitals pin as an outputs
  pinMode(11, OUTPUT);
}

// the loop() method runs over and over again,

void loop()                     
{
  unsigned char i,j;
  while(1) {
    for(i = 0; i < 80; i ++) {
      digitalWrite(11, HIGH);
      delay(1);
      digitalWrite(11, LOW);
      delay(1);
    }
    for(i = 0; i < 100; i ++) {
      digitalWrite(11, HIGH);
      delay(2);
      digitalWrite(11, LOW);
      delay(2);
    }
  }
}
