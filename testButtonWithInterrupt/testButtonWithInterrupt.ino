int button1 = 10;
int redPin =  12;
int greenPin =  15;
int bluePin =  14;
volatile int state = LOW;

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digitals pin as an outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(button1, INPUT);
  digitalWrite(button1, LOW);
  attachInterrupt(digitalPinToInterrupt(2), test, CHANGE); 
}

// the loop() method runs over and over again,

void loop()                     
{
  if(state == HIGH) {
    state = LOW;
    digitalWrite(redPin, HIGH);
    delay(100);
    digitalWrite(greenPin, HIGH);
    delay(100);
    digitalWrite(bluePin, HIGH);
    delay(100);
    digitalWrite(redPin, LOW);
    delay(100);
    digitalWrite(greenPin, LOW);
    delay(100);
    digitalWrite(bluePin, LOW);
    delay(100);
  }
  else {
    digitalWrite(13, HIGH);
    delay(100);
  }
}

void test()
{
  state = !state;
}
