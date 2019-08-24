#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>
#include <MsTimer2.h>

/* Assign a unique ID to this sensor at the same time */
/* Uncomment following line for default Wire bus      */
Adafruit_ADXL343 accel = Adafruit_ADXL343(12345);

int redPin =  16;
int greenPin =  15;
int bluePin =  14;
int button1 = 10;
int sound = 11;
// boolean buttonUp = true;
int state = LOW;
int buttonChangeMode = 3;
int drowningMode =  0;
int fallingMode =  1;
volatile int stateChangeMode = LOW;
int cnt = 0;
boolean timerFlag = false;
boolean arm = false;

/* NeoTrellis M4, etc.                    */
/* Uncomment following line for Wire1 bus */
//Adafruit_ADXL343 accel = Adafruit_ADXL343(12345, &Wire1);

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    ");

  switch(accel.getDataRate())
  {
    case ADXL343_DATARATE_3200_HZ:
      Serial.print  ("3200 ");
      break;
    case ADXL343_DATARATE_1600_HZ:
      Serial.print  ("1600 ");
      break;
    case ADXL343_DATARATE_800_HZ:
      Serial.print  ("800 ");
      break;
    case ADXL343_DATARATE_400_HZ:
      Serial.print  ("400 ");
      break;
    case ADXL343_DATARATE_200_HZ:
      Serial.print  ("200 ");
      break;
    case ADXL343_DATARATE_100_HZ:
      Serial.print  ("100 ");
      break;
    case ADXL343_DATARATE_50_HZ:
      Serial.print  ("50 ");
      break;
    case ADXL343_DATARATE_25_HZ:
      Serial.print  ("25 ");
      break;
    case ADXL343_DATARATE_12_5_HZ:
      Serial.print  ("12.5 ");
      break;
    case ADXL343_DATARATE_6_25HZ:
      Serial.print  ("6.25 ");
      break;
    case ADXL343_DATARATE_3_13_HZ:
      Serial.print  ("3.13 ");
      break;
    case ADXL343_DATARATE_1_56_HZ:
      Serial.print  ("1.56 ");
      break;
    case ADXL343_DATARATE_0_78_HZ:
      Serial.print  ("0.78 ");
      break;
    case ADXL343_DATARATE_0_39_HZ:
      Serial.print  ("0.39 ");
      break;
    case ADXL343_DATARATE_0_20_HZ:
      Serial.print  ("0.20 ");
      break;
    case ADXL343_DATARATE_0_10_HZ:
      Serial.print  ("0.10 ");
      break;
    default:
      Serial.print  ("???? ");
      break;
  }
  Serial.println(" Hz");
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- ");

  switch(accel.getRange())
  {
    case ADXL343_RANGE_16_G:
      Serial.print  ("16 ");
      break;
    case ADXL343_RANGE_8_G:
      Serial.print  ("8 ");
      break;
    case ADXL343_RANGE_4_G:
      Serial.print  ("4 ");
      break;
    case ADXL343_RANGE_2_G:
      Serial.print  ("2 ");
      break;
    default:
      Serial.print  ("?? ");
      break;
  }
  Serial.println(" g");
}

void setup(void)
{
  // initialize the digitals pin as an outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(sound, OUTPUT);
  digitalWrite(button1, LOW);
  attachInterrupt(digitalPinToInterrupt(4), push, FALLING); 
  
  pinMode(drowningMode, OUTPUT);
  pinMode(fallingMode, OUTPUT);
  pinMode(buttonChangeMode, INPUT);
  digitalWrite(buttonChangeMode, LOW);
  attachInterrupt(digitalPinToInterrupt(3), changeMode1, FALLING); 

  MsTimer2::set(1500, stopTimer);

  Serial.begin(9600);
  //while (!Serial);
  Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL343 ... check your connections */
    Serial.println("Ooops, no ADXL343 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL343_RANGE_16_G);
  // accel.setRange(ADXL343_RANGE_8_G);
  // accel.setRange(ADXL343_RANGE_4_G);
  // accel.setRange(ADXL343_RANGE_2_G);

  accel.setDataRate(ADXL343_DATARATE_6_25HZ);

  /* Display some basic information on this sensor */
  displaySensorDetails();
  displayDataRate();
  displayRange();
  Serial.println("");
}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);
Serial.print(cnt);
if(stateChangeMode == LOW) {   //fallingMode
    digitalWrite(drowningMode, LOW);
    digitalWrite(fallingMode, HIGH);
    if(state == HIGH) {
    state = LOW;
    loop();
  }
  else {
    if(event.acceleration.x*event.acceleration.x + event.acceleration.y*event.acceleration.y + event.acceleration.z*event.acceleration.z >= 400.0)
  {
//    Serial.print("Falling! X: "); Serial.print(event.acceleration.x); Serial.print("  ");
//  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
//  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
    if(timerFlag == false) {
    MsTimer2::start();
    timerFlag = true;
    }
    cnt ++;
      }
      if(timerFlag == true && event.acceleration.x*event.acceleration.x + event.acceleration.y*event.acceleration.y + event.acceleration.z*event.acceleration.z >= 150.0) {
        cnt ++;
      }
    }
    if(arm == true) {
       while(state == LOW) {
      digitalWrite(bluePin, HIGH);
      delay(25);
      digitalWrite(bluePin, LOW);
      delay(10);
      digitalWrite(redPin, HIGH);
      delay(25);
      digitalWrite(redPin, LOW);
      delay(10);
      unsigned char i;
      for(i = 0; i < 80; i ++) {
        digitalWrite(sound, HIGH);
        delay(1);
        digitalWrite(sound, LOW);
        delay(1);
      }
      for(i = 0; i < 100; i ++) {
        digitalWrite(sound, HIGH);
        delay(2);
        digitalWrite(sound, LOW);
        delay(2);
      }
    }
    arm = false;
    }
  }
  else if(stateChangeMode == HIGH) {   //drowningMode
    digitalWrite(fallingMode, LOW);
    digitalWrite(drowningMode, HIGH);
    if(state == HIGH) {
    state = LOW;
    loop();
  }
  else {
    if(event.acceleration.y >= 20 || event.acceleration.y <= -20)
  {
    while(state == LOW) {
      digitalWrite(bluePin, HIGH);
      delay(50);
//      digitalWrite(greenPin, HIGH);
//      delay(100);
      digitalWrite(bluePin, LOW);
      delay(25);
//      digitalWrite(greenPin, LOW);
//      delay(100);
      digitalWrite(redPin, HIGH);
      delay(50);
      digitalWrite(redPin, LOW);
      delay(25);
      unsigned char i;
      for(i = 0; i < 80; i ++) {
        digitalWrite(sound, HIGH);
        delay(1);
        digitalWrite(sound, LOW);
        delay(1);
      }
      for(i = 0; i < 100; i ++) {
        digitalWrite(sound, HIGH);
        delay(2);
        digitalWrite(sound, LOW);
        delay(2);
      }
    }
  }
  }
  }
  

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(200);
  
}

void push()
{
  state = !state;
  delay(10);
  Serial.print("Reset!");
}

void changeMode1()
{
  stateChangeMode = !stateChangeMode;
  delay(10);
  Serial.print("Mode changed!");
}

void stopTimer() {
  MsTimer2::stop();
  if(cnt > 1 && cnt < 4) {
   arm = true;
  }
  else {
    arm = false;
  }
  cnt = 0;
  timerFlag = false;
}
