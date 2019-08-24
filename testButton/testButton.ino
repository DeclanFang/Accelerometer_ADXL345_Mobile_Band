int button1 = 10;
boolean buttonUp = true;
int redPin =  12;
int greenPin =  15;
int bluePin =  14;

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digitals pin as an outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(button1, INPUT);
  digitalWrite(button1, LOW);
}

// the loop() method runs over and over again,

void loop()                     
{
  digitalWrite(13, HIGH);
  delay(500);
  if(digitalRead(button1) != HIGH && buttonUp == true) {
    test();
    buttonUp = false;
    }
    else if(digitalRead(button1) == HIGH && buttonUp != true) {
      buttonUp = true;
    }

   delay(10);
}

void test()
{
  digitalWrite(redPin, HIGH);
  delay(500);
  digitalWrite(greenPin, HIGH);
  delay(500);
  digitalWrite(bluePin, HIGH);
  delay(500);
  digitalWrite(redPin, LOW);
  delay(500);
  digitalWrite(greenPin, LOW);
  delay(500);
  digitalWrite(bluePin, LOW);
  delay(500);
}
