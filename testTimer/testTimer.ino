#include <MsTimer2.h>

int cnt = 0;

void setup() 
{
  pinMode(13, OUTPUT);
  MsTimer2::set(1000, stopTimer);
  attachInterrupt(digitalPinToInterrupt(2), beginTimer, FALLING);
}

void loop() {
   cnt += 1;
   Serial.print(cnt);
   Serial.print("-");
   if(cnt > 9) {
    digitalWrite(13, HIGH);
   }
   else {
    digitalWrite(13, LOW);
   }
   delay(100);
}

void beginTimer() {
  MsTimer2::start();
}

void stopTimer() {
  cnt = 0;
  MsTimer2::stop();
}
