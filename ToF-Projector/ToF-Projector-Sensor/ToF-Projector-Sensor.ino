// include the library code
#include <Wire.h>
#include <VL53L1X.h>

#define DETECTION_DISTANCE 1300 //Distance that counts as detection

//I/O Constants
#define IN_1      14
#define IN_2      15
#define IN_3      16
#define OUT_SELF  8
#define OUT_1     9
#define OUT_2     10
#define OUT_3     11

// ToF variables
VL53L1X sensor;
int dist = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  //set the I/O Pins
  pinMode(IN_1,INPUT);
  pinMode(IN_2,INPUT);
  pinMode(IN_3,INPUT);
  pinMode(OUT_SELF,OUTPUT);
  pinMode(OUT_1,OUTPUT);
  pinMode(OUT_2,OUTPUT);
  pinMode(OUT_3,OUTPUT);
  digitalWrite(OUT_SELF,LOW);
  digitalWrite(OUT_1,LOW);
  digitalWrite(OUT_2,LOW);
  digitalWrite(OUT_3,LOW);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.print("Failed to detect and initialize sensor!");
    while (1);
  }
  //maybe use long distance in example?

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);
}

void loop() {
  //get the distance in mm
  dist = sensor.read();
  Serial.print(dist);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  //detect a Person
  if (dist<=DETECTION_DISTANCE){
    Serial.print("DETECTED");
    digitalWrite(OUT_SELF,HIGH);
  } else {
    digitalWrite(OUT_SELF,LOW);
  }
  Serial.println();

  //handle the other Inputs and set them to outputs
  digitalWrite(OUT_1, digitalRead(IN_1));
  digitalWrite(OUT_2, digitalRead(IN_2));
  digitalWrite(OUT_3, digitalRead(IN_3));
}