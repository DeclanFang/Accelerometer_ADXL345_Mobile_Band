int buttonChangeMode = 3;
int drowningMode =  0;
int fallingMode =  1;
volatile int stateChangeMode = LOW;

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digitals pin as an outputs
  pinMode(drowningMode, OUTPUT);
  pinMode(fallingMode, OUTPUT);
  pinMode(buttonChangeMode, INPUT);
  digitalWrite(buttonChangeMode, LOW);
  attachInterrupt(digitalPinToInterrupt(3), changeMode1, FALLING); 
}

// the loop() method runs over and over again,

void loop()                     
{
  if(stateChangeMode == LOW) {   //fallingMode
    digitalWrite(drowningMode, LOW);
    digitalWrite(fallingMode, HIGH);
  }
  else if(stateChangeMode == HIGH) {   //drowningMode
    digitalWrite(fallingMode, LOW);
    digitalWrite(drowningMode, HIGH);
  }
}

void changeMode1()
{
  stateChangeMode = !stateChangeMode;
  delay(10);
}
